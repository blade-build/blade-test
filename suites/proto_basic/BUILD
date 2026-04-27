# Smoke suite for blade's proto_library rule — ported from
# blade-build/example/proto/ with the .proto sources rewritten in
# proto3 (upstream used implicit proto2, which protoc 33+ warns
# about noisily).
#
# What this suite pins down:
#   * proto_library invokes protoc to generate C++ sources from one
#     or more .proto files, including ones in sub-directories.
#   * Generated .pb.cc / .pb.h compile cleanly and land at
#     build_dir-relative paths that downstream cc_tests can include
#     as ``suites/proto_basic/contact.pb.h`` etc. (blade injects the
#     build output dir onto consumers' -I automatically).
#   * The resulting archive links against the system libprotobuf
#     advertised by BLADE_ROOT's proto_library_config
#     (``protobuf_libs = ['#protobuf', '#pthread']``) — a missing
#     or ABI-incompatible libprotobuf regresses into a link-time
#     failure on this suite.
#
# Two .proto files are used so that the subdirectory case
# (``dir/contact.proto``) also gets covered; see contact_test.cc for
# the descriptor-level assertion that distinguishes them.

proto_library(
    name = 'contact_proto',
    srcs = [
        'contact.proto',
        'dir/contact.proto',
    ],
    visibility = ['PUBLIC'],
)

cc_test(
    name = 'contact_test',
    srcs = 'contact_test.cc',
    deps = [
        ':contact_proto',
    ],
)
