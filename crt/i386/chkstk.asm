OPTION DOTNAME

.686P
.XMM
.MODEL FLAT



;PUBLIC __chkstk
;PUBLIC __alloca_probe
PUBLIC __alloca_probe_16
.code



__alloca_probe_16:

    push ecx


    lea ecx, [esp + 8]


    sub ecx, eax


    and ecx, 15


    add eax, ecx


    jnc l1


    mov eax, 0ffffffffh
l1:

    pop ecx







__chkstk:
__alloca_probe:



    push ecx


    lea ecx, [esp + 8]


    cmp eax, 4096
    jl .l_LessThanAPage

.l_MoreThanAPage:


    sub ecx, 4096
    test [ecx], eax


    sub eax, 4096
    cmp eax, 4096
    jge .l_MoreThanAPage

.l_LessThanAPage:


    sub ecx, eax
    test [ecx], eax


    mov eax, esp


    mov esp, ecx


    mov ecx, [eax]


    mov eax, [eax + 4]
    push eax


    ret
END


