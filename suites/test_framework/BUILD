# Minimal test framework — drop-in replacement for gtest/gtest_main.
#
# Usage in cc_test targets:
#   cc_test_config(
#       gtest_libs = ['//suites/test_framework:test_framework'],
#       gtest_main_libs = ['//suites/test_framework:test_main'],
#   )

cc_library(
    name = 'test_framework',
    hdrs = 'test_framework.h',
    visibility = 'PUBLIC',
)

cc_library(
    name = 'test_main',
    srcs = 'test_main.cc',
    hdrs = [],
    deps = ':test_framework',
    visibility = 'PUBLIC',
    # The framework owns a global test registry. Such cross-module mutable
    # state is not safe to share through an auto-exported shared library
    # (the registrar and main() would each see their own copy), so keep it
    # static even inside a `dynamic_link` test. See the cc_library
    # `generate_dynamic` docs / "Windows DLL support".
    generate_dynamic = False,
)
