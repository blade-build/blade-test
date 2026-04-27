// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Author: chen3feng <chen3feng@gmail.com>

#include "suites/cc_basic/hello.h"

#include <gtest/gtest.h>

namespace blade_test::cc_basic {

TEST(HelloTest, GreetsByName) {
    EXPECT_EQ("Hello, blade!", Greet("blade"));
}

TEST(HelloTest, EmptyNameFallsBackToWorld) {
    EXPECT_EQ("Hello, world!", Greet(""));
}

}  // namespace blade_test::cc_basic
