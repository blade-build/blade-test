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
    cc_test(
        name='vcpkg_test',
        srcs=[
            'fmt_test.cc',
            'gflags_test.cc',
            'glog_test.cc',
            'openssl_test.cc',
        ],
        # glog 0.7's <glog/logging.h> requires the consumer to define this
        # export macro.
        defs=['GLOG_USE_GLOG_EXPORT'],
        deps=[
            'vcpkg#fmt:fmt',
            # glog before gflags: glog references gflags symbols, so on a static
            # link gflags must come after it on the command line.
            'vcpkg#glog:glog',
            'vcpkg#gflags:gflags',
            'vcpkg#openssl:crypto',
        ],
    )
