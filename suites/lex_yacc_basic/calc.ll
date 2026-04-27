/* Minimal flex scanner companion to calc.yy.
 *
 * Tokenizes:
 *   - integer literals  → NUMBER with yylval = atoi(yytext)
 *   - '+', '-', '*'     → returned as their literal character codes
 *   - whitespace        → skipped
 *   - anything else     → returned as-is so the parser can complain
 *                         via yyerror() (exercised by the error case
 *                         in calc_test.cc).
 *
 * Portability / build notes:
 *   - `%option noyywrap` avoids having to link `-lfl`; the default
 *     yywrap() always returning 1 (EOF = done) is what we want for a
 *     single-buffer calculator.
 *   - `%option nounput` + `%option noinput` silence the "unused
 *     function" warnings that flex 2.6 emits under `-Wall` when those
 *     helpers are not referenced — the stock blade cc rule adds
 *     warnings for this target (warning='yes' in BUILD).
 *   - We rely on flex's runtime helper `yy_scan_string` to accept
 *     an in-memory string from the C++ driver; this is part of the
 *     flex runtime, not POSIX, but the lex_yacc_library rule already
 *     requires flex, so it is an acceptable dependency.
 */

%option noyywrap
%option nounput
%option noinput

%{
#include <stdlib.h>

/* Pull in the bison-generated token ids (NUMBER, YYSTYPE, yylval). */
#include "suites/lex_yacc_basic/calc.yy.hh"
%}

%%

[ \t\r]+        { /* skip horizontal whitespace */ }

[0-9]+          { yylval = atoi(yytext); return NUMBER; }

"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }

\n              { /* end of input line — let the parser close out */ }

.               { return yytext[0]; /* unknown char; parser will yyerror */ }

%%
