// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Smoke test: consume `:foo` as a DLL (dynamic_link=True in BUILD) and use an
// exported polymorphic class + global variable across the DLL boundary.
//
// On Windows we declare the imported symbols by defining FOO_EXPORT to
// __declspec(dllimport) BEFORE including the header. This forces the consumer
// to reference the *imported* vtable/RTTI and the import-table data slot, which
// only link if Blade's auto-generated .def exports the vtable/RTTI (and the
// global with the DATA keyword). On non-Windows FOO_EXPORT stays empty and
// imports resolve through the GOT -- so the same test runs everywhere.
//
// This verifies the vtable/RTTI export fix end-to-end without depending on
// Blade automating the consumer-side import macro.

#if defined(_WIN32)
#define FOO_EXPORT __declspec(dllimport)
#endif
#include "suites/cc_dll_export/foo.h"

#include <memory>

#include "suites/test_framework/test_framework.h"

namespace foo {

TEST(DllExportTest, VtableAndDataImportable) {
    // Constructing the object stores the imported vtable pointer; calling a
    // virtual method through it forces use of the imported vtable.
    std::unique_ptr<Greeter> greeter(new Greeter());
    EXPECT_EQ("Hello, blade!", greeter->Greet("blade"));

    // Reading the imported global verifies DATA export + dllimport: a missing
    // dllimport would yield the import-table pointer, not 42.
    EXPECT_EQ(42, g_answer);
}

}  // namespace foo
