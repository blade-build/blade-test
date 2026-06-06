// Copyright (c) 2026 The Blade Authors.
// All rights reserved.

#include "suites/cc_dll_export/foo.h"

namespace foo {

int g_answer = 42;

Greeter::Greeter() = default;

Greeter::~Greeter() = default;

std::string Greeter::Greet(const std::string& who) const {
    return "Hello, " + who + "!";
}

}  // namespace foo
