// Copyright (c) 2026 The Blade Authors.
// All rights reserved.

// cgo wrappers over two Blade cc_library targets (a C one and a C++ one). The
// `import "C"` preamble includes their headers and calls into both; Blade
// supplies the include dirs (CGO_CFLAGS) and archives + C++ runtime
// (CGO_LDFLAGS). Kept in a non-test file because Go disallows cgo directly in
// *_test.go -- greet_test.go calls these wrappers instead.
package check

/*
#include "suites/cgo_basic/greeter_c/greeter_c.h"
#include "suites/cgo_basic/greeter_cxx/greeter_cxx.h"
*/
import "C"

// GreetC returns the greeting from the C cc_library.
func GreetC() string { return C.GoString(C.greet_c()) }

// GreetCxx returns the greeting from the C++ cc_library (extern "C" entry).
func GreetCxx() string { return C.GoString(C.greet_cxx()) }
