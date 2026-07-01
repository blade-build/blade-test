// Copyright (c) 2026 The Blade Authors.
// All rights reserved.

// Package greeter provides a trivial greeting helper.
//
// Kept intentionally minimal — it exists so the go_basic suite can exercise
// blade-build's go_library / go_test / go_binary wiring end-to-end. Mirrors
// suites/py_basic/greeter.py and suites/cc_basic/hello.cc so the suites stay
// symmetrical when diagnosing cross-language regressions.
package greeter

// Greet returns "Hello, <name>!" for non-empty names, else "Hello, world!".
func Greet(name string) string {
	if name == "" {
		name = "world"
	}
	return "Hello, " + name + "!"
}
