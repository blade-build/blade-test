@echo off

call "%PROGRAMFILES(x86)%\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat" -startdir=none -arch=x64 -host_arch=x64
:: call "%PROGRAMFILES(x86)%\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat" -startdir=none -arch=x86 -host_arch=x64

set "PATH=%PATH%;%CD%\..\blade-build"