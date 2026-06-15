// Copyright (c) 2026 The Blade Authors.
// All rights reserved.

#include <string>

#include "suites/objc_basic/greeting.h"
#include "suites/test_framework/test_framework.h"

namespace blade_test::objc_basic {

TEST(ObjcBasic, ObjectiveC) {
    EXPECT_EQ(std::string("hello-from-objc"), objc_greeting());
}

TEST(ObjcBasic, ObjectiveCxx) {
    EXPECT_EQ(std::string("hello-from-objcxx+ns"), objcxx_greeting());
}

}  // namespace blade_test::objc_basic
