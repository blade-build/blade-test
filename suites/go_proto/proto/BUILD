# proto_library that also emits Go: the generated `.pb.go` lands in the build
# dir (out of the source tree) and consuming go targets pick it up through a
# `go build -overlay`. `option go_package` in item.proto must be this dir's
# in-module import path. Requires proto_library_config(protoc_go_plugin=...) in
# BLADE_ROOT.
proto_library(
    name = 'item_proto',
    srcs = 'item.proto',
    visibility = ['PUBLIC'],
)
