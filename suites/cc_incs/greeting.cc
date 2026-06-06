// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Author: chen3feng <chen3feng@gmail.com>

#include "greeting.h"  // resolvable only through incs = ['include']

namespace blade_test::cc_incs {

std::string Greet() {
#ifdef GREETING_EXCITED
    return "Hi!!!";
#else
    return "Hi";  // if defs weren't threaded into the MSVC compile, we'd get this
#endif
}

}  // namespace blade_test::cc_incs
