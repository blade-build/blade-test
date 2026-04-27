# Smoke suite for the Python toolchain wiring (py_library + py_test).
#
# This suite intentionally mirrors cc_basic: a trivial library with one
# pure function plus a test that exercises two behaviors. It protects
# the contract between blade-build/v3 and py_library / py_test — any
# regression in python target discovery, test discovery, or the
# `blade test` runner surfaces here before it reaches real users.

py_library(
    name = 'greeter',
    srcs = 'greeter.py',
    visibility = 'PUBLIC',
)

py_test(
    name = 'greeter_test',
    srcs = 'greeter_test.py',
    deps = ':greeter',
)
