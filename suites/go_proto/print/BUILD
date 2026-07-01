# go_binary built in file mode from its srcs, importing the generated protobuf
# package -- covers the file-mode overlay path (go_test above covers package
# mode).
go_binary(
    name = 'print',
    srcs = 'main.go',
    deps = '//suites/go_proto/proto:item_proto',
)
