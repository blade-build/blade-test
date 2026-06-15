// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// vcpkg#glog:glog smoke -- glog links (it pulls vcpkg#gflags) and logging runs.

#include <glog/logging.h>

#include "suites/test_framework/test_framework.h"

namespace blade_test::vcpkg_basic {

TEST(VcpkgGlog, LogRuns) {
    // Before InitGoogleLogging glog writes to stderr; the point is that the
    // symbols resolve and the call runs without crashing.
    LOG(INFO) << "blade-test vcpkg glog smoke";
    LOG(WARNING) << "blade-test vcpkg glog warning";
    EXPECT_TRUE(true);
}

TEST(VcpkgGlog, CheckMacro) {
    CHECK_EQ(1 + 1, 2);
    EXPECT_TRUE(true);
}

}  // namespace blade_test::vcpkg_basic
