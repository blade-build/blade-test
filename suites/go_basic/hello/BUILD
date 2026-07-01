# go_binary built from its srcs (file mode), depending on a go_library in the
# same module -- exercises the cross-package dependency edge and visibility.

go_binary(
    name = 'hello',
    srcs = 'hello.go',
    deps = '//suites/go_basic/greeter:greeter',
)
