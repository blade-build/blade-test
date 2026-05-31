// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Author: chen3feng <chen3feng@gmail.com>

#include "suites/cc_basic/farewell/farewell.h"
#include "suites/cc_basic/hello.h"

#include "suites/test_framework/test_framework.h"

namespace blade_test::cc_basic {

// `:hello` is in the *same* package as this test, so under dynamic_link its DLL
// lands next to the exe and the loader finds it via the default exe-directory
// search.
TEST(CrossPackageDllTest, SamePackageDll) {
    EXPECT_EQ("Hello, blade!", Greet("blade"));
}

// `farewell` is in a *different* package, so its DLL lands in another output
// directory. It is found only because blade flattens every dependency DLL into
// the test's runfiles and prepends that directory to PATH at run time; the
// default exe-directory search would not locate it.
TEST(CrossPackageDllTest, CrossPackageDll) {
    EXPECT_EQ("Goodbye, blade!", Farewell("blade"));
}

}  // namespace blade_test::cc_basic
