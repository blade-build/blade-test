# A library in its own package, used by a cross-package dynamic_link test in
# //suites/cc_basic. Under dynamic_link its DLL is emitted into this package's
# output directory (not next to the test exe), so it resolves only via blade's
# runtime DLL discovery (flattened runfiles + PATH) -- see blade-build #1181.

cc_library(
    name = 'farewell',
    hdrs = 'farewell.h',
    srcs = 'farewell.cc',
    visibility = 'PUBLIC',
)
