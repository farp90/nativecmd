OPTION DOTNAME

.686P
.XMM
.MODEL FLAT
ASSUME CS:NOTHING, DS:NOTHING, ES:NOTHING, FS:NOTHING, GS:NOTHING

rip = 0





.PROC MACRO name
    name PROC FRAME
    _name:
ENDM


.ENDP MACRO name
    name ENDP
ENDM


.ASCII MACRO text
    DB text
ENDM


.ASCIZ MACRO text
    DB text, 0
ENDM





.code64 MACRO
    .code
ENDM

.code32 MACRO
    .code
    .586P
ENDM

.code16 MACRO
    ASSUME nothing
    .text SEGMENT use16
ENDM

.endcode16 MACRO
    .text ENDS
ENDM

.bss MACRO
    .DATA?
    ASSUME nothing
ENDM




.align MACRO alignment
    ALIGN alignment
ENDM

.byte MACRO args:VARARG
    db args
ENDM

.short MACRO args:VARARG
    dw args
ENDM

.word MACRO args:VARARG
    dw args
ENDM

.long MACRO args:VARARG
    dd args
ENDM

.double MACRO args:VARARG
    dq args
ENDM

.org MACRO value
    ORG value
ENDM

.fill MACRO repeat, size, value

ENDM





UNIMPLEMENTED MACRO name
ENDM


.code

PUBLIC _SwitchToFiber@4
_SwitchToFiber@4:

    mov edx, fs:[018h]


    mov eax, [edx+010h]


    mov [eax+0b8h], ebx
    mov [eax+0b4h], esi
    mov [eax+0b0h], edi
    mov [eax+0c8h], ebp


    mov ebx, [esp]
    mov [eax+0cch], ebx


    cmp dword ptr [eax+014h], 010007h OR 010008h
    jnz NoFpuStateSave


    fstsw [eax+034h]
    fstcw [eax+030h]


    cmp byte ptr ds:[07ffe0278h], 0
    jnz NoFpuStateSave
    stmxcsr [eax+028h]

NoFpuStateSave:


    mov [eax+0d8h], esp


    mov ecx, [edx+0fb4h]
    mov [eax+02e4h], ecx
    mov ecx, [edx+01a8h]
    mov [eax+02e8h], ecx


    mov ecx, [edx+00h]
    mov [eax+04h], ecx
    mov ecx, [edx+08h]
    mov [eax+0ch], ecx
    mov ecx, [edx+0f78h]
    mov [eax+02e0h], ecx


    mov ecx, [esp+4]
    mov [edx+010h], ecx


    mov esi, [ecx+04h]
    mov [edx+00h], esi
    mov esi, [ecx+08h]
    mov [edx+04h], esi
    mov esi, [ecx+0ch]
    mov [edx+08h], esi
    mov esi, [ecx+010h]
    mov [edx+0e0ch], esi
    mov esi, [ecx+02e0h]
    mov [edx+0f78h], esi
    mov esi, [ecx+02e8h]
    mov [edx+01a8h], esi


    cmp dword ptr [eax+014h], 010007h OR 010008h
    jnz NoFpuStateRestore


    mov esi, [eax+034h]
    cmp si, word ptr [ecx+034h]
    jnz StatusWordChanged


    mov esi, [eax+030h]
    cmp si, word ptr [ecx+030h]
    jz ControlWordEqual

StatusWordChanged:


    mov word ptr [ecx+038h], 00FFFFh
    fldenv [ecx+030h]

ControlWordEqual:


    cmp byte ptr ds:[07ffe0278h], 0
    jnz NoFpuStateRestore
    ldmxcsr [ecx+028h]

NoFpuStateRestore:


    mov esi, [ecx+0b4h]
    mov edi, [ecx+0b0h]
    mov ebx, [ecx+0b8h]
    mov ebp, [ecx+0c8h]
    mov esp, [ecx+0d8h]


    mov eax, [ecx+02e4h]
    mov [edx+0fb4h], eax


    jmp dword ptr [ecx+0cch]

END
