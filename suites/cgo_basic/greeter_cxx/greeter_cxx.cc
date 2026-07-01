#include "suites/cgo_basic/greeter_cxx/greeter_cxx.h"
#include <string>
// std::string pulls in the C++ runtime; cgo links through the C driver, so this
// only links because Blade adds -lstdc++/-lc++ to CGO_LDFLAGS for cc deps.
static std::string g;
extern "C" const char* greet_cxx(void) {
    g = std::string("c") + "xx";
    return g.c_str();
}
