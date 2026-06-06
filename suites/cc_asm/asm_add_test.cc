// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Author: chen3feng <chen3feng@gmail.com>

#include "suites/test_framework/test_framework.h"

extern "C" int asm_add(int a, int b);  // defined in asm_add.asm

namespace blade_test::cc_asm {

// Passes only if asm_add.asm was assembled (ml64) and linked -- i.e. blade
// routed the .asm source to the MSVC 'as' rule rather than cl.exe.
TEST(CcAsmTest, AssemblesAndLinks) {
    EXPECT_EQ(5, asm_add(2, 3));
    EXPECT_EQ(-1, asm_add(2, -3));
}

}  // namespace blade_test::cc_asm
