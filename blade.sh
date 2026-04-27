#!/bin/bash
# blade.sh — wrapper for invoking the sibling blade-build (v3) from this test workspace.
#
# Assumptions:
#   * blade-test/ and blade-build/ live side-by-side (the blade-build v3 branch).
#   * Host has python3.12 available at /opt/homebrew/bin/python3.12 (symlinked into
#     tools/python-shim/python3 so the launcher's `_check_python` sees 3.10+).
#   * Host has ninja, protoc, thrift, swig, mvn, scalac, go, javac on PATH.

set -euo pipefail

HERE="$(cd "$(dirname "$0")" && pwd)"
BLADE_BUILD_DIR="${BLADE_BUILD_DIR:-$HERE/../blade-build}"

if [[ ! -x "$BLADE_BUILD_DIR/blade" ]]; then
    echo "[blade.sh] cannot find blade launcher at $BLADE_BUILD_DIR/blade" >&2
    echo "[blade.sh] set BLADE_BUILD_DIR=/path/to/blade-build or place the two repos side-by-side" >&2
    exit 1
fi

# Put our python3 shim (-> 3.12) first so the launcher's `_check_python`
# resolves a 3.10+ interpreter even if system python3 is older.
export PATH="$HERE/tools/python-shim:$PATH"
# Belt-and-suspenders: the launcher honors BLADE_PYTHON_INTERPRETER.
export BLADE_PYTHON_INTERPRETER="${BLADE_PYTHON_INTERPRETER:-$HERE/tools/python-shim/python3}"

# On macOS the system `gcc` binary is actually an Apple clang alias. Blade's
# toolchain.cc_is('gcc') check is substring-based (and CC defaults to 'gcc'),
# so without this it would emit gcc-only link flags like `-static-libgcc` that
# clang rejects. Exporting CC/CXX makes the detection accurate.
if [[ "$(uname -s)" == "Darwin" ]]; then
    export CC="${CC:-clang}"
    export CXX="${CXX:-clang++}"
fi

exec "$BLADE_BUILD_DIR/blade" "$@"
