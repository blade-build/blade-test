// Copyright (c) 2026 The Blade Authors.
// All rights reserved.

// A go_binary (file-mode build) that imports the generated protobuf package --
// pins that the overlay is also visible to `go build <file>` (file mode), not
// just package mode.
package main

import (
	"fmt"

	pb "blade.test/goproto/proto"
)

func main() {
	fmt.Println((&pb.Item{Name: "widget", Quantity: 7}).String())
}
