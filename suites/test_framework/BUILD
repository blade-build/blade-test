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
)
