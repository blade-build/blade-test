// Copyright (c) 2026 The Blade Authors.
// All rights reserved.

// A trivial command that imports the greeter library. Exercises go_binary
// (built in file mode from its srcs) with a cross-package dependency on a
// go_library in the same module.
package main

import (
	"fmt"

	"blade.test/gobasic/greeter"
)

func main() {
	fmt.Println(greeter.Greet("blade"))
}
