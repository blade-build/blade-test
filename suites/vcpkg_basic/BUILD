# Smoke for blade's native vcpkg support (`vcpkg#<port>:<lib>`): install +
# build + link + run against real ports (fmt, gflags, glog, openssl).
#
# Gated on $VCPKG_ROOT (see //BLADE_ROOT) so the suite is inert unless vcpkg is
# explicitly enabled -- the dedicated `vcpkg` CI job sets it, as does a local
# run that exports VCPKG_ROOT. When unset this BUILD declares no targets, so the
# rest of //suites/... (and blade-build's cross-repo e2e-smoke) is unaffected.
# Reading os.environ here needs the unrestricted DSL, granted to this dir by
# //BLADE_ROOT's global_config(unrestricted_dsl_dirs=...).
import os

if os.environ.get('VCPKG_ROOT'):
    # glog 0.7's <glog/logging.h> requires the consumer to define this export
    # macro.
    _msvc = blade.cc_toolchain.cc_vendor == 'msvc'
    # vcpkg uses different library basenames on MSVC: openssl keeps the `lib`
    # prefix (libcrypto.lib) and gflags ships the threaded static target as
    # gflags_static.lib, whereas on POSIX they are libcrypto.a / libgflags.a.
    _crypto = 'vcpkg#openssl:libcrypto' if _msvc else 'vcpkg#openssl:crypto'
    _gflags = 'vcpkg#gflags:gflags_static' if _msvc else 'vcpkg#gflags:gflags'
    _defs = ['GLOG_USE_GLOG_EXPORT']
    if _msvc:
        # glog/gflags include <windows.h>, which (a) defines min/max macros that
        # break the C++ std/glog templates -> NOMINMAX; (b) defines an ERROR
        # macro that collides with glog's abbreviated severities ->
        # GLOG_NO_ABBREVIATED_SEVERITIES; and the headers default to dllimport
        # decoration -> GFLAGS_IS_A_DLL=0 for the static gflags we link.
        _defs += ['NOMINMAX', 'GLOG_NO_ABBREVIATED_SEVERITIES',
                  'GFLAGS_IS_A_DLL=0']
    cc_test(
        name='vcpkg_test',
        srcs=[
            'fmt_test.cc',
            'gflags_test.cc',
            'glog_test.cc',
            'openssl_test.cc',
        ],
        defs=_defs,
        # fmt's headers static_assert on /utf-8 under MSVC.
        extra_cppflags=(['/utf-8'] if _msvc else []),
        # System libraries the ports pull in on Windows (their .pc Libs.private,
        # which blade's MSVC vcpkg path does not auto-resolve yet): glog ->
        # dbghelp (Sym*), gflags -> shlwapi (PathMatchSpec), openssl ->
        # advapi32/user32/crypt32/ws2_32/gdi32/bcrypt.
        extra_linkflags=(['dbghelp.lib', 'shlwapi.lib', 'advapi32.lib',
                          'user32.lib', 'crypt32.lib', 'ws2_32.lib',
                          'gdi32.lib', 'bcrypt.lib'] if _msvc else []),
        deps=[
            'vcpkg#fmt:fmt',
            # glog before gflags: glog references gflags symbols, so on a static
            # link gflags must come after it on the command line.
            'vcpkg#glog:glog',
            _gflags,
            _crypto,
        ],
    )
