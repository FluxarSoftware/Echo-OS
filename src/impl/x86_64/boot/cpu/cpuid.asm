section .text
global check_cpuid
extern error

check_cpuid:
    pushfq           ; Push flags onto stack
    pop rax          ; Pop flags into rax

    mov rcx, rax     ; Save original flags in rcx
    xor rax, 1 << 21 ; Toggle the ID bit in rax

    push rax         ; Push modified flags onto stack
    popfq            ; Pop flags from stack into flags register

    pushfq           ; Push flags onto stack again
    pop rax          ; Pop flags into rax

    push rcx         ; Push original flags onto stack
    popfq            ; Pop flags from stack into flags register

    cmp rax, rcx     ; Compare original and modified flags
    je .no_cpuid     ; If equal, CPUID is not supported

    ret

.no_cpuid:
    mov al, "C"
    jmp error
