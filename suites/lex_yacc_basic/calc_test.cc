// Copyright (c) 2026 The Blade Authors.
// All rights reserved.
//
// Smoke test for blade's `lex_yacc_library` rule.
//
// The suite wires a minimal flex scanner (calc.ll) and bison grammar
// (calc.yy) together into the target :parser, wraps it in a C++
// driver (calc_driver.{h,cc}) and exercises four properties:
//
//   1. End-to-end: a valid expression produces the expected int.
//   2. Operator precedence: `*` binds tighter than `+`/`-`.
//   3. Whitespace between tokens is skipped.
//   4. A syntactically invalid input surfaces through the error
//      channel rather than the result channel.
//
// Together these lock down the contract that the lex_yacc_library
// rule: (a) invokes flex and bison in the right order, (b) exposes
// the generated .hh header so dependents can see token definitions,
// and (c) links the resulting .o files into a cc_library that can be
// consumed by an ordinary cc_test.

#include "suites/lex_yacc_basic/calc_driver.h"

#include <optional>
#include <string>

#include "suites/test_framework/test_framework.h"

TEST(LexYaccBasic, EvaluatesSimpleExpression) {
    const auto value = blade_calc::Evaluate("1+2");
    ASSERT_TRUE(value.has_value());
    EXPECT_EQ(*value, 3);
}

// Grammar encodes `term := term '*' NUMBER` under `expr`, so `*`
// must bind tighter than `+`/`-`. 2*3+4 therefore evaluates to 10,
// and 1+2*3 evaluates to 7.
TEST(LexYaccBasic, RespectsOperatorPrecedence) {
    EXPECT_EQ(blade_calc::Evaluate("2*3+4"), std::optional<int>{10});
    EXPECT_EQ(blade_calc::Evaluate("1+2*3"), std::optional<int>{7});
    EXPECT_EQ(blade_calc::Evaluate("10-2*3"), std::optional<int>{4});
}

// Whitespace between tokens is skipped by the scanner — another
// piece of the flex contract we want locked down.
TEST(LexYaccBasic, IgnoresWhitespaceBetweenTokens) {
    EXPECT_EQ(blade_calc::Evaluate("  7\t+  3 "), std::optional<int>{10});
}

// A syntactically invalid input should surface via the error
// channel, not as a (silently-zero) successful result.
TEST(LexYaccBasic, ReportsSyntaxError) {
    std::string err;
    const auto value = blade_calc::Evaluate("1 + + 2", &err);
    EXPECT_FALSE(value.has_value());
    EXPECT_FALSE(err.empty())
            << "yyerror() message should have been forwarded";
}
