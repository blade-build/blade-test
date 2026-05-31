// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Author: chen3feng <chen3feng@gmail.com>

#include "suites/cc_export_map/api.h"

#include <memory>

#include "suites/test_framework/test_framework.h"

namespace mylib {

// The library is linked dynamically (see BUILD), so on Linux it is built as a
// shared object with `--version-script=api.map` applied. The public API must
// still resolve at load/run time -- if the export map dropped these symbols,
// the dynamic link would fail. (The internal helper mylib::Decorate is hidden
// but reachable from inside the library, as Greet's result shows.)
TEST(ExportMapTest, PublicApiIsUsable) {
    std::unique_ptr<Api> api(Create());
    EXPECT_EQ("<<Hello, blade!>>", api->Greet("blade"));
}

}  // namespace mylib
