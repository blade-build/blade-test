// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Author: chen3feng <chen3feng@gmail.com>

#pragma once

#include <string>

namespace blade_test::cc_incs {

// Reachable only via the target's `incs = ['include']` -- there is no
// full-path "suites/cc_incs/include/greeting.h" include anywhere. Its
// implementation's return value depends on the per-target `defs` macro
// GREETING_EXCITED. Together these exercise per-target incs + defs, which
// the MSVC compile rules historically dropped.
std::string Greet();

}  // namespace blade_test::cc_incs
