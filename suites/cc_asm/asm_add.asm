; Copyright (c) 2026 The Blade Authors.
; All rights reserved.
;
; Minimal x64 MASM source to smoke-test blade's MSVC assembler (ml64) rule.
; int asm_add(int a, int b) -> a + b
; Microsoft x64 calling convention: a = ECX, b = EDX, result in EAX.

PUBLIC asm_add

_TEXT SEGMENT

asm_add PROC
    mov eax, ecx
    add eax, edx
    ret
asm_add ENDP

_TEXT ENDS

END
