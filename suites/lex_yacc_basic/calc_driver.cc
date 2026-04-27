// Copyright (c) 2026 The Blade Authors.
// All rights reserved.

#include "suites/lex_yacc_basic/calc_driver.h"

#include <mutex>
#include <string>

// Bridge between the grammar file and this C++ driver.
//
// Subtle point worth nailing down: blade's `lex_yacc_library` names
// its source files `.ll` / `.yy` and therefore the generated files
// end in `.cc` — which means **flex and bison output is compiled by
// blade's C++ compiler rule**. The symbols flex/bison emit
// (`yylex`, `yyparse`, `yy_scan_string`, `yy_delete_buffer`, etc.)
// and the callbacks the grammar calls into (our
// `blade_calc_set_result`, `blade_calc_record_error`) are therefore
// all C++-linkage symbols: they undergo C++ name mangling, not C
// linkage.
//
// So we deliberately do *not* wrap any of these in `extern "C"` —
// doing so would mangle-mismatch the references inside
// libparser.a's calc.yy.cc.o and cause "symbol not found" at link.
//
// `yy_scan_string` / `yy_delete_buffer` are flex runtime helpers
// (not POSIX). The `yy_buffer_state` forward-declaration below
// mirrors flex's own private typedef so we don't have to include
// the scanner's internals; this contract has been stable across
// flex 2.5 / 2.6.
int  yyparse(void);

// flex runtime — feed an in-memory buffer instead of stdin.
typedef struct yy_buffer_state* YY_BUFFER_STATE;
YY_BUFFER_STATE yy_scan_string(const char* str);
void            yy_delete_buffer(YY_BUFFER_STATE buf);

// Callbacks invoked from inside calc.yy's semantic actions /
// yyerror(); we own the storage behind them.
void blade_calc_set_result(int value);
void blade_calc_record_error(const char* message);

namespace {

// The flex-generated scanner and bison-generated parser are both
// built on global state (yyin, yylval, the parser stack). Guard the
// whole evaluate-one-expression path with a mutex so concurrent
// callers can't race on those globals — gtest runs tests serially
// within a process by default, but we still want Evaluate() itself
// to be thread-safe as a library function.
std::mutex& Singleton() {
    static std::mutex m;
    return m;
}

// Slots the grammar callbacks write into for the *current* call to
// Evaluate(). Only touched while Singleton() is held.
struct CallState {
    bool has_result = false;
    int  result = 0;
    bool has_error = false;
    std::string error_message;
};

CallState* g_active = nullptr;

}  // namespace

void blade_calc_set_result(int value) {
    if (g_active != nullptr) {
        g_active->has_result = true;
        g_active->result = value;
    }
}

void blade_calc_record_error(const char* message) {
    if (g_active != nullptr) {
        g_active->has_error = true;
        g_active->error_message = (message != nullptr) ? message : "";
    }
}

namespace blade_calc {

std::optional<int> Evaluate(std::string_view expression,
                            std::string* error_out) {
    // yy_scan_string takes a NUL-terminated C string; make a local
    // copy so string_view callers don't have to guarantee that.
    const std::string buffer(expression);

    std::lock_guard<std::mutex> lock(Singleton());

    CallState state;
    g_active = &state;

    YY_BUFFER_STATE flex_buffer = yy_scan_string(buffer.c_str());
    const int parse_rc = yyparse();
    yy_delete_buffer(flex_buffer);

    g_active = nullptr;

    if (parse_rc != 0 || state.has_error || !state.has_result) {
        if (error_out != nullptr) {
            *error_out = state.has_error
                                 ? state.error_message
                                 : std::string("parse failed");
        }
        return std::nullopt;
    }
    return state.result;
}

}  // namespace blade_calc
