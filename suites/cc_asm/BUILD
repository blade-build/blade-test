# Smoke for the MSVC assembler (ml64/ml) rule: a .asm source assembled and
# linked into a cc_test. Guarded to MSVC (the 'as' tool, i.e. ml64, is present);
# GCC/Clang assemble .s/.S via the cc driver and have no MASM, so this suite is
# simply absent there.

if blade.cc_toolchain.tool('as') is not None:
    cc_library(
        name = 'asm_add',
        srcs = ['asm_add.asm'],
        hdrs = [],  # pure assembly, no public headers
        visibility = 'PUBLIC',
    )

    cc_test(
        name = 'cc_asm_test',
        srcs = ['asm_add_test.cc'],
        deps = [':asm_add'],
    )
