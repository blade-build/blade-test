// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Author: chen3feng <chen3feng@gmail.com>

#pragma once

#include <string>

namespace mylib {

// Public API of this library. Only these symbols are listed in api.map and
// therefore exported from the shared library; everything else (e.g. the
// external-linkage helper mylib::Decorate in api.cc) is hidden by the
// `local: *;` clause.
class Api {
 public:
    std::string Greet(const std::string& who) const;
};

Api* Create();

}  // namespace mylib
