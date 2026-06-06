// Copyright (c) 2026 The Blade Authors.
// All rights reserved.

#pragma once

// Default: no decoration.
//
// - Building this library: Blade auto-generates the .def on Windows, so no
//   __declspec(dllexport) is ever needed -- FOO_EXPORT stays empty.
// - Consuming as a Windows DLL: the user defines
//   FOO_EXPORT=__declspec(dllimport) BEFORE including this header (see
//   foo_test.cc), so the class vtable/RTTI and the global are imported.
// - Non-Windows: FOO_EXPORT stays empty; imports resolve through the GOT with
//   no decoration.
#ifndef FOO_EXPORT
#define FOO_EXPORT
#endif

#include <string>

namespace foo {

// Polymorphic class. The out-of-line virtual functions make this the canonical
// "exported class": the vtable/RTTI live in the DLL. Consuming it via
// __declspec(dllimport) references the *imported* vtable, so it links only if
// Blade's auto-.def actually exports the vtable/RTTI symbols.
class FOO_EXPORT Greeter {
 public:
    // Special members are declared out-of-line on purpose. With a dllimport
    // class MSVC also imports the constructor; auto-export only exports symbols
    // actually emitted in the DLL, and an *implicit* ctor used only by the
    // consumer is never emitted there. Declaring it out-of-line forces the DLL
    // to emit and export it. (A factory function avoids this entirely.)
    Greeter();
    virtual ~Greeter();
    virtual std::string Greet(const std::string& who) const;
};

// Exported global variable. Without __declspec(dllimport) on the consumer side
// the compiler would read the import-table slot (a pointer) instead of the
// value -- so this also exercises the DATA export + dllimport path.
FOO_EXPORT extern int g_answer;

}  // namespace foo
