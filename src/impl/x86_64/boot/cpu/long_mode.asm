section .text
global check_long_mode
extern error

check_long_mode:
    mov eax, 0x80000000
    cpuid 
    cmp eax, 0x80000001
    jb .no_long_mode

    mov eax, 0x80000001
    cpuid 
    test edx, 1 << 29
    jz .no_long_mode
    ret
.no_long_mode:
    mov al, "L"
    jmp error
