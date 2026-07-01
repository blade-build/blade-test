// Copyright (c) 2026 The Blade Authors.
// All rights reserved.

package check

import "testing"

func TestCgoLinksCLibrary(t *testing.T) {
	if got := GreetC(); got != "c" {
		t.Fatalf("GreetC() = %q, want \"c\"", got)
	}
}

func TestCgoLinksCxxLibrary(t *testing.T) {
	if got := GreetCxx(); got != "cxx" {
		t.Fatalf("GreetCxx() = %q, want \"cxx\"", got)
	}
}
