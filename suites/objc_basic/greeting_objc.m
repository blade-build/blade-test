// Copyright (c) 2026 The Blade Authors.
// All rights reserved.

#import <Foundation/Foundation.h>

#include "suites/objc_basic/greeting.h"

const char* objc_greeting(void) {
    return [@"hello-from-objc" UTF8String];
}
