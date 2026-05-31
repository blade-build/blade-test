// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Author: chen3feng <chen3feng@gmail.com>

#include "suites/cc_basic/farewell/farewell.h"

#include <string>

namespace blade_test::cc_basic {

std::string Farewell(std::string_view name) {
    std::string out = "Goodbye, ";
    if (name.empty()) {
        out += "world";
    } else {
        out.append(name.data(), name.size());
    }
    out += "!";
    return out;
}

}  // namespace blade_test::cc_basic
