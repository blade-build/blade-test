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

cc_library(
    name = 'world',
    hdrs = 'world.h',
    srcs = 'world.cc',
    deps = ':hello',
    visibility = 'PUBLIC',
)

cc_binary(
    name = 'hello-world',
    srcs = 'main.cc',
    deps = [':hello', ':world'],
)

cc_test(
    name = 'hello_test',
    srcs = 'hello_test.cc',
    deps = ':hello',
)

# Same test, linked dynamically: `:hello` is built as a shared library
# (a DLL + import library on Windows) and loaded at run time, while the
# test framework stays static (see //suites/test_framework). This is the
# smoke for the Windows DLL path — the cases must still run and pass.
cc_test(
    name = 'hello_dynamic_test',
    srcs = 'hello_test.cc',
    deps = ':hello',
    dynamic_link = True,
)

# A dynamic_link test that also depends on a *cross-package* library
# (//suites/cc_basic/farewell). That dependency's DLL is emitted into a
# different output directory than this test's exe, so it is found only via
# blade's runtime DLL discovery (flattened runfiles + PATH) -- not the default
# exe-directory search that covers the same-package `:hello` DLL.
cc_test(
    name = 'cross_package_dynamic_test',
    srcs = 'cross_package_dynamic_test.cc',
    deps = [
        ':hello',
        '//suites/cc_basic/farewell:farewell',
    ],
    dynamic_link = True,
)
