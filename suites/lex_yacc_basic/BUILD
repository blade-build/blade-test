# Smoke suite for blade's lex_yacc_library rule.
#
# Wires a minimal flex scanner (calc.ll) and bison grammar (calc.yy)
# together into a single :parser target, then drives it from a C++
# cc_library + cc_test. The point is to lock down the contract that
# lex_yacc_library:
#
#   - accepts srcs as a 2-tuple [lex_file, yacc_file] (in that order);
#   - invokes flex then bison with bison's -d so a header is emitted;
#   - exposes the generated header (<yacc>.hh) to downstream deps
#     (the scanner .ll #includes it for the token definitions, and
#     so does calc_driver.cc indirectly via our own calc_driver.h);
#   - produces a library that can be linked by an ordinary cc_test.
#
# Host toolchain:
#   - flex (any 2.x is fine; macOS ships 2.6, ubuntu 22.04 ships 2.6).
#   - bison (any version from 2.3 upward — we intentionally stick to
#     the POSIX yacc / bison-2.3 feature set so the stock macOS
#     `bison 2.3` and Linux CI's `bison 3.x` both accept the grammar;
#     see the comment block at the top of calc.yy for details).

lex_yacc_library(
    name = 'parser',
    srcs = [
        'calc.ll',
        'calc.yy',
    ],
    # flex 2.6's generated scanner triggers -Wsign-compare inside
    # its own internal buffer bookkeeping (unsigned yy_n_chars
    # compared against signed YY_BUF_SIZE). It's noise outside our
    # control, and BLADE_ROOT promotes -Wsign-compare to an error
    # for the whole workspace via the default cc warning set, so we
    # suppress just that one diagnostic here rather than reaching
    # for the sledgehammer (warning='no', which blade rightly
    # reserves for third-party code).
    extra_cppflags = [
        '-Wno-sign-compare',
    ],
)

cc_library(
    name = 'calc_driver',
    srcs = 'calc_driver.cc',
    hdrs = 'calc_driver.h',
    deps = ':parser',
)

cc_test(
    name = 'calc_test',
    srcs = 'calc_test.cc',
    deps = ':calc_driver',
)
