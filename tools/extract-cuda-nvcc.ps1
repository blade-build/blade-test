#!/usr/bin/env pwsh
<#
.SYNOPSIS
    Extract a usable nvcc toolchain from a CUDA Windows installer, without
    running the (multi-GB, admin) full install.

.DESCRIPTION
    `cuda_X.Y.Z_windows.exe` is a 7-Zip archive whose payload is laid out per
    component, e.g.
        cuda_nvcc\nvcc\bin\nvcc.exe
        libnvvm\nvvm\nvvm\bin\cicc.exe
        cuda_cudart\cudart\include\cuda_runtime.h
        cuda_cccl\thrust\include\...
    The full install merges these into one CUDA root. This script unpacks only
    the components needed to compile .cu files and merges them the same way, so
    `<Destination>\bin\nvcc.exe` is a working, portable nvcc — a few hundred MB
    instead of a full ~3 GB install. Handy for CI and reproducible dev setups.

    Requires 7-Zip (auto-detected, or pass -SevenZip). No admin rights needed.

.PARAMETER Installer
    Path to the CUDA Windows installer (cuda_*_windows.exe).

.PARAMETER Destination
    Directory to assemble the CUDA root into (created if missing). Add
    `<Destination>\bin` to PATH to use nvcc.

.PARAMETER SevenZip
    Path to 7z.exe. Defaults to `7z` on PATH, else the standard 7-Zip install.

.PARAMETER Force
    Overwrite/merge into a non-empty Destination.

.EXAMPLE
    .\extract-cuda-nvcc.ps1 `
        -Installer C:\Users\cf\Downloads\cuda_13.2.1_windows.exe `
        -Destination C:\develop\CUDA-13.2.1
#>
[CmdletBinding()]
param(
    [Parameter(Mandatory)][string]$Installer,
    [Parameter(Mandatory)][string]$Destination,
    [string]$SevenZip,
    [switch]$Force
)

$ErrorActionPreference = 'Stop'

function Resolve-SevenZip([string]$hint) {
    if ($hint) {
        if (Test-Path $hint) { return $hint }
        throw "7-Zip not found at -SevenZip '$hint'."
    }
    $cmd = Get-Command 7z -ErrorAction SilentlyContinue
    if ($cmd) { return $cmd.Source }
    foreach ($p in @("$env:ProgramFiles\7-Zip\7z.exe", "${env:ProgramFiles(x86)}\7-Zip\7z.exe")) {
        if (Test-Path $p) { return $p }
    }
    throw "7-Zip not found. Install it (https://7-zip.org) or pass -SevenZip <path to 7z.exe>."
}

# Component subtree inside the installer  ->  its place under the CUDA root.
# Stable across CUDA 11/12/13. Drop cudart/cccl if you only need nvcc to emit
# PTX (no <cuda_runtime.h>); keep them to compile real .cu.
$layout = [ordered]@{
    'cuda_nvcc\nvcc'     = '.'      # bin\ (nvcc, ptxas, nvlink, cudafe++, crt\, nvcc.profile), include\
    'libnvvm\nvvm\nvvm'  = 'nvvm'   # cicc, nvvm64 dll, libdevice  ->  <root>\nvvm
    'cuda_cudart\cudart' = '.'      # cuda_runtime.h etc., lib\x64, runtime DLLs
    'cuda_cccl\thrust'   = '.'      # thrust / cub / cccl headers pulled in by <cuda_runtime>
}

if (-not (Test-Path $Installer)) { throw "Installer not found: $Installer" }
$Installer   = (Resolve-Path $Installer).Path
$Destination = [System.IO.Path]::GetFullPath($Destination)
$sevenZipExe = Resolve-SevenZip $SevenZip

if ((Test-Path $Destination) -and -not $Force -and
    (Get-ChildItem $Destination -Force -ErrorAction SilentlyContinue)) {
    throw "Destination '$Destination' is not empty. Pass -Force to merge into it."
}
New-Item -ItemType Directory -Force -Path $Destination | Out-Null

$temp = Join-Path ([System.IO.Path]::GetTempPath()) ("cuda-nvcc-" + [System.IO.Path]::GetRandomFileName())
New-Item -ItemType Directory -Force -Path $temp | Out-Null
try {
    # Extract only the top-level component folders we need (not the whole 2+ GB).
    $components = $layout.Keys | ForEach-Object { ($_ -split '\\')[0] } | Sort-Object -Unique
    $filters = $components | ForEach-Object { "$_\*" }
    Write-Host "Extracting [$($components -join ', ')] from $(Split-Path $Installer -Leaf) ..."
    & $sevenZipExe x -y "-o$temp" $Installer @filters | Out-Null
    if ($LASTEXITCODE -ne 0) { throw "7-Zip extraction failed (exit $LASTEXITCODE)." }

    foreach ($subtree in $layout.Keys) {
        $from = Join-Path $temp $subtree
        if (-not (Test-Path $from)) { Write-Warning "component not in installer, skipped: $subtree"; continue }
        $to = if ($layout[$subtree] -eq '.') { $Destination } else { Join-Path $Destination $layout[$subtree] }
        New-Item -ItemType Directory -Force -Path $to | Out-Null
        Write-Host "  merge $subtree -> $to"
        # robocopy merges trees and is quiet; exit codes < 8 are success.
        robocopy $from $to /E /NFL /NDL /NJH /NJS /NP | Out-Null
        if ($LASTEXITCODE -ge 8) { throw "robocopy failed for '$subtree' (exit $LASTEXITCODE)." }
    }
} finally {
    Remove-Item -Recurse -Force $temp -ErrorAction SilentlyContinue
}

$nvcc = Join-Path $Destination 'bin\nvcc.exe'
if (-not (Test-Path $nvcc)) { throw "nvcc.exe missing at '$nvcc' after extraction." }

Write-Host ""
Write-Host "nvcc ready: $nvcc"
& $nvcc --version
Write-Host ""
Write-Host "Add to PATH:  $(Join-Path $Destination 'bin')"
# Emit the bin dir as the last line so callers can capture it.
Join-Path $Destination 'bin'
