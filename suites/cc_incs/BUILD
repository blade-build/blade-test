# Regression suite for per-target `incs` and `defs` on the cc compile path.
#
# Unlike cc_basic (full-path includes, no defs), here the header is reachable
# ONLY via `incs = ['include']` and the library's behavior depends on a
# per-target `defs` macro. On MSVC these per-target ninja vars were historically
# dropped from the cc/cxx compile rules, so a cc_basic-style suite never caught
# it. Portable: builds the same on GCC/Clang and MSVC.

cc_library(
    name = 'greeting',
    srcs = 'greeting.cc',
    hdrs = 'include/greeting.h',
    incs = ['include'],
    defs = ['GREETING_EXCITED'],
    visibility = 'PUBLIC',
)

cc_test(
    name = 'cc_incs_test',
    srcs = 'cc_incs_test.cc',
    incs = ['include'],
    deps = ':greeting',
)
