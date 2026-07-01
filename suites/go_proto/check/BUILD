# go_test that imports the generated protobuf package. Its dep on the
# proto_library is what pulls the overlay in (blade collects transitive `go_pb`
# outputs and writes the `-overlay` map for this test's `go test -c`).
go_test(
    name = 'item_test',
    srcs = 'item_test.go',
    deps = '//suites/go_proto/proto:item_proto',
)
