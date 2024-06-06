global print_string

section .data
vga_buffer: equ 0xb8000
columns: equ 80
rows: equ 25

section .text
bits 32

print_string:
    ; Receives:
    ;   si: pointer to the string

    pusha
    mov edi, vga_buffer

.print_char:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    int 0x10
    jmp .print_char

.done:
    popa
    ret
