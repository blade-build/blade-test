// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Author: chen3feng <chen3feng@gmail.com>

#include "suites/cc_export_map/api.h"

namespace mylib {

// Has external linkage (not static, not in an anonymous namespace), so without
// an export map it would land in the shared library's dynamic symbol table.
// It is deliberately omitted from api.map: the `local: *;` clause keeps it
// hidden. It is still callable within the library (Greet uses it below).
std::string Decorate(const std::string& s) {
    return "<<" + s + ">>";
}

std::string Api::Greet(const std::string& who) const {
    return Decorate("Hello, " + who + "!");
}

Api* Create() {
    return new Api();
}

}  // namespace mylib
