// Smoke binary for the C/C++ toolchain wiring — tests executable linking.
// Author: chen3feng <chen3feng@gmail.com>

#include "suites/cc_basic/hello.h"

#include <iostream>

int main() {
    std::cout << blade_test::cc_basic::Greet("blade") << std::endl;
    return 0;
}
