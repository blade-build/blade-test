/* Minimal yacc grammar for a line-oriented integer calculator.
 *
 * Grammar:
 *     line   : expr          { store result, done }
 *     expr   : expr '+' term
 *            | expr '-' term
 *            | term
 *     term   : term '*' NUMBER
 *            | NUMBER
 *
 * Driver contract (see calc_driver.h):
 *   - `yyparse()` reads one expression from the flex scanner (which
 *     has been pointed at an in-memory buffer by the driver) and
 *     stores the resulting int into the driver-provided slot via the
 *     `blade_calc_set_result()` callback.
 *   - `yyerror()` likewise forwards the message to the driver so the
 *     C++ side can surface it without touching stderr.
 *
 * Portability notes:
 *   - Deliberately stays within the POSIX yacc / bison 2.3 feature set
 *     so macOS's stock `bison 2.3` and Linux CI's `bison 3.x` both
 *     accept it. No `%code`, no `%define`, no `%locations`.
 *   - `%union` is not needed — the semantic type is plain `int`,
 *     which we set via the classic `#define YYSTYPE int` escape hatch.
 *   - Declares `yylex`/`yyerror` prototypes so `-Wimplicit` stays
 *     quiet under modern clang/gcc.
 */

%{
#include <stdio.h>
#include <stdlib.h>

/* Forward decls for the driver-side bridge; defined in calc_driver.cc. */
void blade_calc_set_result(int value);
void blade_calc_record_error(const char* message);

int  yylex(void);
void yyerror(const char* message);

/* The semantic type for every grammar symbol. We use the classic
 * `#define YYSTYPE int` escape hatch instead of bison 3.x's
 * `%define api.value.type {int}`, because macOS still ships the
 * stock bison 2.3 which predates %define. */
#define YYSTYPE int
%}

%token NUMBER

%%

line
    : expr                 { blade_calc_set_result($1); }
    ;

expr
    : expr '+' term        { $$ = $1 + $3; }
    | expr '-' term        { $$ = $1 - $3; }
    | term                 { $$ = $1; }
    ;

term
    : term '*' NUMBER      { $$ = $1 * $3; }
    | NUMBER               { $$ = $1; }
    ;

%%

void yyerror(const char* message) {
    blade_calc_record_error(message);
}
