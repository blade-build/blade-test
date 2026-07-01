# go_test that calls into both a C and a C++ cc_library through cgo. The cgo
# lives in greet.go (Go disallows `import "C"` in *_test.go); greet_test.go
# exercises the wrappers. The deps pull each archive + include dir into the
# cgo build.
go_test(
    name = 'cgo_test',
    srcs = [
        'greet.go',
        'greet_test.go',
    ],
    deps = [
        '//suites/cgo_basic/greeter_c:greeter_c',
        '//suites/cgo_basic/greeter_cxx:greeter_cxx',
    ],
)
