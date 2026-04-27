#!/bin/bash
# blade.sh — thin wrapper for invoking the sibling blade-build (v3) launcher
# from this test workspace.
#
# Layout assumption:
#   blade-test/   (this repo)
#   blade-build/  (sibling checkout of chen3feng/blade-build, v3 branch)
#
# Override with BLADE_BUILD_DIR=/path/to/blade-build if the two repos are not
# side-by-side.
#
# Host requirements (blade-build v3):
#   * python3 >= 3.10 on PATH (the launcher's _check_python honors
#     BLADE_PYTHON_INTERPRETER if your default python3 is older; set it in
#     your shell, we do not inject one here).
#   * C/C++ toolchain (clang on macOS, gcc on Linux) — blade auto-detects.
#   * ninja, protoc, thrift, swig, mvn, scalac, go, javac as needed by the
#     specific suites under suites/.

set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"
BLADE_BUILD_DIR="${BLADE_BUILD_DIR:-$HERE/../blade-build}"

if [[ ! -x "$BLADE_BUILD_DIR/blade" ]]; then
    echo "[blade.sh] cannot find blade launcher at $BLADE_BUILD_DIR/blade" >&2
    echo "[blade.sh] set BLADE_BUILD_DIR=/path/to/blade-build or place the two repos side-by-side" >&2
    exit 1
fi

exec "$BLADE_BUILD_DIR/blade" "$@"
