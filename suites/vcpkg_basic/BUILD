# Smoke for blade's native vcpkg support (`vcpkg#<port>:<lib>`): install +
# build + link + run against real ports (fmt, gflags, glog, openssl).
#
# Declared unconditionally -- blade installs the ports only when this target is
# actually built (demand-driven), so the shared //suites/... run and
# blade-build's e2e-smoke, which exclude vcpkg_basic, pull in no vcpkg
# dependency. The dedicated `vcpkg` CI jobs build this target with VCPKG_ROOT set.
_msvc = blade.cc_toolchain.cc_vendor == 'msvc'

# vcpkg uses different library basenames on MSVC: openssl keeps the `lib` prefix
# (libcrypto.lib) and gflags ships the threaded static target as
# gflags_static.lib, whereas on POSIX they are libcrypto.a / libgflags.a.
_crypto = 'vcpkg#openssl:libcrypto' if _msvc else 'vcpkg#openssl:crypto'
_gflags = 'vcpkg#gflags:gflags_static' if _msvc else 'vcpkg#gflags:gflags'

# glog 0.7's <glog/logging.h> requires the consumer to define this export macro.
_defs = ['GLOG_USE_GLOG_EXPORT']
if _msvc:
    # glog/gflags include <windows.h>, which (a) defines min/max macros that
    # break the C++ std/glog templates -> NOMINMAX; (b) defines an ERROR macro
    # that collides with glog's abbreviated severities ->
    # GLOG_NO_ABBREVIATED_SEVERITIES; and the headers default to dllimport
    # decoration -> GFLAGS_IS_A_DLL=0 for the static gflags we link.
    _defs += ['NOMINMAX', 'GLOG_NO_ABBREVIATED_SEVERITIES', 'GFLAGS_IS_A_DLL=0']

cc_test(
    name='vcpkg_test',
    srcs=[
        'fmt_test.cc',
        'gflags_test.cc',
        'glog_test.cc',
        'openssl_test.cc',
    ],
    defs=_defs,
    # The Windows system libs these ports pull in (glog -> dbghelp, gflags ->
    # shlwapi, openssl -> advapi32/crypt32/ws2_32/...) are resolved automatically
    # from each port's .pc Libs.private now (blade-build #1322).
    deps=[
        'vcpkg#fmt:fmt',
        # glog before gflags: glog references gflags symbols, so on a static link
        # gflags must come after it on the command line.
        'vcpkg#glog:glog',
        _gflags,
        _crypto,
    ],
)
