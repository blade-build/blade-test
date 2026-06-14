// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// vcpkg#gflags:gflags smoke -- flag definition + lookup link and run.

#include <gflags/gflags.h>

#include <string>

#include "suites/test_framework/test_framework.h"

DEFINE_int32(blade_vcpkg_answer, 42, "smoke-test flag");

namespace blade_test::vcpkg_basic {

TEST(VcpkgGflags, FlagDefault) {
    EXPECT_EQ(42, FLAGS_blade_vcpkg_answer);
}

TEST(VcpkgGflags, SetCommandLineOption) {
    gflags::SetCommandLineOption("blade_vcpkg_answer", "7");
    EXPECT_EQ(7, FLAGS_blade_vcpkg_answer);
}

}  // namespace blade_test::vcpkg_basic
