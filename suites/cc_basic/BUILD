# Smoke suite for the C/C++ toolchain wiring (cc_library + cc_test + gtest).
#
# The gtest/gtest_main libraries are wired up in //BLADE_ROOT via
# cc_test_config.gtest_libs / gtest_main_libs, so cc_test targets here
# only need to depend on the library under test.

cc_library(
    name = 'hello',
    hdrs = 'hello.h',
    srcs = 'hello.cc',
    visibility = 'PUBLIC',
)

cc_test(
    name = 'hello_test',
    srcs = 'hello_test.cc',
    deps = ':hello',
)
