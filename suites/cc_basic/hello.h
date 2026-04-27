// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Author: chen3feng <chen3feng@gmail.com>

#pragma once

#include <string>
#include <string_view>

namespace blade_test::cc_basic {

// Returns "Hello, <name>!" for non-empty names, or "Hello, world!"
// when `name` is empty. Kept intentionally trivial — this suite is
// a smoke test for the C/C++ toolchain wiring (cc_library + cc_test
// + gtest linkage), not for library logic.
std::string Greet(std::string_view name);

}  // namespace blade_test::cc_basic
