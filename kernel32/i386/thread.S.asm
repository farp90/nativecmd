
OPTION DOTNAME

.686P
.XMM
.MODEL FLAT
ASSUME CS:NOTHING, DS:NOTHING, ES:NOTHING, FS:NOTHING, GS:NOTHING

.code

EXTERN _BaseThreadStartup@8:PROC
EXTERN _BaseProcessStartup@4:PROC

PUBLIC _BaseThreadStartupThunk@0
PUBLIC _BaseProcessStartThunk@0

_BaseThreadStartupThunk@0:


    xor ebp, ebp

    push ebx
    push eax
    push 0
    jmp _BaseThreadStartup@8

_BaseProcessStartThunk@0:


    xor ebp, ebp

    push eax
    push 0
    jmp _BaseProcessStartup@4

END
