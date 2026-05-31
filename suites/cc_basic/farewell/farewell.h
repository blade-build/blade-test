// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Author: chen3feng <chen3feng@gmail.com>

#pragma once

#include <string>
#include <string_view>

namespace blade_test::cc_basic {

// Returns "Goodbye, <name>!" (or "Goodbye, world!" for an empty name).
//
// This lives in a *separate* package from the test that uses it, so that
// under `dynamic_link` its DLL is emitted into a different output directory
// than the test executable. That exercises blade's runtime DLL discovery
// (flattened runfiles + PATH); the default exe-directory search would not
// find it. See blade-build #1181.
std::string Farewell(std::string_view name);

}  // namespace blade_test::cc_basic
