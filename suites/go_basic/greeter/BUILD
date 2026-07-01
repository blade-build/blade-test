# Smoke suite for the Go toolchain wiring (go_library + go_test).
#
# Mirrors py_basic / cc_basic: a trivial library with one pure function plus a
# test exercising two behaviors. Pins the contract between blade-build/v3 and
# the modules-only Go rules (#1405): go target discovery, per-target go.mod
# module discovery (the module go.mod lives one level up at
# //suites/go_basic), the go_library compile-check, and the `go test` runner.

go_library(
    name = 'greeter',
    srcs = 'greeter.go',
    visibility = 'PUBLIC',
)

go_test(
    name = 'greeter_test',
    srcs = 'greeter_test.go',
    deps = ':greeter',
)
