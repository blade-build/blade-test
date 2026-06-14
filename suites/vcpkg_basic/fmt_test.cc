// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// vcpkg#fmt:fmt smoke -- the library builds, links, and runs.

#include <fmt/format.h>

#include "suites/test_framework/test_framework.h"

namespace blade_test::vcpkg_basic {

TEST(VcpkgFmt, Format) {
    EXPECT_EQ("answer = 42", fmt::format("answer = {}", 42));
}

TEST(VcpkgFmt, JoinAndPad) {
    EXPECT_EQ("[  7]", fmt::format("[{:3}]", 7));
}

}  // namespace blade_test::vcpkg_basic
