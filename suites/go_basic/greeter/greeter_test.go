// Copyright (c) 2026 The Blade Authors.
// All rights reserved.

// Smoke tests for the greeter package, run via `go test` (Blade's go_test).
// Standard-library testing only, so a failure points at blade's go_test wiring
// rather than a test harness.
package greeter

import "testing"

func TestGreetsByName(t *testing.T) {
	if got := Greet("blade"); got != "Hello, blade!" {
		t.Fatalf("Greet(\"blade\") = %q, want %q", got, "Hello, blade!")
	}
}

func TestEmptyNameFallsBackToWorld(t *testing.T) {
	if got := Greet(""); got != "Hello, world!" {
		t.Fatalf("Greet(\"\") = %q, want %q", got, "Hello, world!")
	}
}
