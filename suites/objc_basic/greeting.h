// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Greetings implemented in Objective-C (.m) and Objective-C++ (.mm), consumed
// from C++.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Defined in greeting_objc.m (Objective-C, C linkage).
const char* objc_greeting(void);

#ifdef __cplusplus
}

// Defined in greeting_objcxx.mm (Objective-C++, C++ linkage).
const char* objcxx_greeting();
#endif
