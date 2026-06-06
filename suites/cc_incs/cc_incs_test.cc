// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Author: chen3feng <chen3feng@gmail.com>

#include "greeting.h"  // resolvable only through incs = ['include']

#include "suites/test_framework/test_framework.h"

namespace blade_test::cc_incs {

// Passes only if greeting.cc was compiled with the per-target inc dir AND the
// per-target GREETING_EXCITED define. On MSVC, before the compile rules
// threaded ${includes}/${cppflags}, this suite would fail to compile (header
// not found) or return "Hi" (define dropped).
TEST(CcIncsTest, PerTargetIncsAndDefsAreThreaded) {
    EXPECT_EQ("Hi!!!", Greet());
}

}  // namespace blade_test::cc_incs
