// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// C++ driver for the calc.ll / calc.yy lex_yacc_library target.
//
// The lex/yacc pair is generated with the default `yy` prefix and
// talks to the outside world through three C-linkage symbols:
//
//   - int  yyparse(void)          — the bison entry point.
//   - YY_BUFFER_STATE yy_scan_string(const char*)  — flex helper
//     that lets us feed an in-memory buffer instead of stdin.
//   - void yy_delete_buffer(YY_BUFFER_STATE)        — matching cleanup.
//
// Plus two callbacks that the grammar itself calls to surface the
// parse outcome back to us without touching globals across
// translation-unit boundaries:
//
//   - blade_calc_set_result(int)       — the successful result.
//   - blade_calc_record_error(const char*) — the yyerror() message.
//
// We wrap all of that in a single C++ function so the test can stay
// high-level: `CalcEval("1+2*3")` returns `std::optional<int>`.

#ifndef SUITES_LEX_YACC_BASIC_CALC_DRIVER_H_
#define SUITES_LEX_YACC_BASIC_CALC_DRIVER_H_

#include <optional>
#include <string>
#include <string_view>

namespace blade_calc {

// Evaluate a single expression of the form `int (+|-|*) int ...`.
// On success returns the computed value. On a syntax error returns
// std::nullopt and stores the message in *error_out (if non-null).
std::optional<int> Evaluate(std::string_view expression,
                            std::string* error_out = nullptr);

}  // namespace blade_calc

#endif  // SUITES_LEX_YACC_BASIC_CALC_DRIVER_H_
