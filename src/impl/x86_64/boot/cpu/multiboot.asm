global check_multiboot
extern error

section .text
bits 32

check_multiboot:
    cmp eax, 0x36d76289
    jne .no_multiboot
    ret

.no_multiboot:
    mov eax, "M"
    call error
