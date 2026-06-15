// Copyright (c) 2026 The Blade Authors.
// All rights reserved.

#import <Foundation/Foundation.h>

#include <string>

#include "suites/objc_basic/greeting.h"

const char* objcxx_greeting() {
    // Objective-C++ mixes ObjC (NSString) with C++ (std::string).
    static std::string s = std::string("hello-from-objcxx+") + [@"ns" UTF8String];
    return s.c_str();
}
