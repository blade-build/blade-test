// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Author: chen3feng <chen3feng@gmail.com>

// Generated headers land at paths that mirror the .proto sources:
//   build64_release/suites/proto_basic/contact.pb.h
//   build64_release/suites/proto_basic/dir/contact.pb.h
// Blade injects the build output dir onto consumers' -I flags, so the
// source-relative includes below resolve automatically.
#include "suites/proto_basic/contact.pb.h"
#include "suites/proto_basic/dir/contact.pb.h"

#include "suites/test_framework/test_framework.h"

namespace {

using blade_test::proto_basic::Person;
using blade_test::proto_basic::sub::Person2;

// Round-trips a Person message through SerializeToString /
// ParseFromString. The point isn't to test protobuf itself — that's
// upstream's job — but to prove that proto_library actually ran
// protoc, emitted C++ sources, compiled them, and linked the result
// against libprotobuf. Any breakage in that pipeline fails this test
// at either compile, link, or serialization time.
TEST(ProtoBasic, PersonRoundTripsThroughBinarySerialization) {
    Person original;
    original.set_name("Ada");
    original.set_id(1815);
    original.set_email("ada@example.com");

    auto* phone = original.add_phone();
    phone->set_number("555-0100");
    phone->set_type(Person::MOBILE);

    std::string wire;
    ASSERT_TRUE(original.SerializeToString(&wire));
    EXPECT_FALSE(wire.empty());

    Person parsed;
    ASSERT_TRUE(parsed.ParseFromString(wire));
    EXPECT_EQ("Ada", parsed.name());
    EXPECT_EQ(1815, parsed.id());
    EXPECT_EQ("ada@example.com", parsed.email());
    ASSERT_EQ(1, parsed.phone_size());
    EXPECT_EQ("555-0100", parsed.phone(0).number());
    EXPECT_EQ(Person::MOBILE, parsed.phone(0).type());
}

// Separate test for the subdirectory .proto so a regression that
// breaks protoc's treatment of nested paths fails in isolation
// rather than getting lumped into the Person test above.
TEST(ProtoBasic, Person2FromSubdirectoryCompilesAndRoundTrips) {
    Person2 original;
    original.set_name("Grace");
    original.set_id(1906);

    std::string wire;
    ASSERT_TRUE(original.SerializeToString(&wire));

    Person2 parsed;
    ASSERT_TRUE(parsed.ParseFromString(wire));
    EXPECT_EQ("Grace", parsed.name());
    EXPECT_EQ(1906, parsed.id());
    EXPECT_TRUE(parsed.email().empty());  // proto3 default
}

// Descriptor introspection doubles as a cheap sanity check that the
// two .proto files wound up in distinct packages — a blade regression
// that merged them into one proto_library output would collapse the
// descriptors and break this assertion.
TEST(ProtoBasic, DescriptorsRecordDistinctPackages) {
    EXPECT_EQ("blade_test.proto_basic",
              Person::descriptor()->file()->package());
    EXPECT_EQ("blade_test.proto_basic.sub",
              Person2::descriptor()->file()->package());
}

}  // namespace
