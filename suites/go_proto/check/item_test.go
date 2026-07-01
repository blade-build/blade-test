// Copyright (c) 2026 The Blade Authors.
// All rights reserved.

// Exercises the proto->Go overlay end to end: it imports the generated package
// (blade.test/goproto/proto, produced by //suites/go_proto/proto:item_proto and
// injected via `go build -overlay`) and the protobuf runtime, then round-trips
// a message. A go_test builds in package mode, so this also pins that the
// overlay is visible to package-mode `go test -c`.
package check

import (
	"testing"

	"google.golang.org/protobuf/proto"

	pb "blade.test/goproto/proto"
)

func TestItemRoundTrip(t *testing.T) {
	in := &pb.Item{Name: "widget", Quantity: 7}
	wire, err := proto.Marshal(in)
	if err != nil {
		t.Fatalf("marshal: %v", err)
	}
	out := &pb.Item{}
	if err := proto.Unmarshal(wire, out); err != nil {
		t.Fatalf("unmarshal: %v", err)
	}
	if out.GetName() != "widget" || out.GetQuantity() != 7 {
		t.Fatalf("round-trip mismatch: got name=%q quantity=%d", out.GetName(), out.GetQuantity())
	}
}
