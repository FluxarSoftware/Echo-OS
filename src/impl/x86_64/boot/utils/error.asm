; Color definitions
COLOR_BLACK         equ 0x00
COLOR_BLUE          equ 0x01
COLOR_GREEN         equ 0x02
COLOR_CYAN          equ 0x03
COLOR_RED           equ 0x04
COLOR_MAGENTA       equ 0x05
COLOR_BROWN         equ 0x06
COLOR_LIGHT_GREY    equ 0x07
COLOR_DARK_GREY     equ 0x08
COLOR_LIGHT_BLUE    equ 0x09
COLOR_LIGHT_GREEN   equ 0x0A
COLOR_LIGHT_CYAN    equ 0x0B
COLOR_LIGHT_RED     equ 0x0C
COLOR_LIGHT_MAGENTA equ 0x0D
COLOR_LIGHT_BROWN   equ 0x0E
COLOR_WHITE         equ 0x0F

global kernel_panic, error
extern print_string

section .text
bits 32

error_label:
    pusha
    mov si, error_msg
    call print_string
    mov ax, [error_code]
    call print_hex
    call kernel_panic
    popa
    hlt

kernel_panic:
    mov ax, 0x03
    int 0x10

    mov ah, 0x02
    xor bh, bh
    xor dx, dx
    int 0x10

    mov ax, 0x4F00
    mov bx, COLOR_LIGHT_RED
    call set_text_color 

    mov si, panic_msg 
    call print_string

    cli
    hlt

print_hex:
    push ax         ; Save AX on stack
    @ mov cx, 4       ; 4 digits in a 16-bit number
.loop:
    rol ax, 4
    mov bl, al
    and bl, 0x0F
    add bl, 0x30    ; Convert to ASCII '0'-'9'
    cmp bl, 0x39
    jbe .print_digit
    add bl, 7
.print_digit:
    mov ah, 0x0E
    int 0x10
    loop .loop      ; Loop 4 times (4 bits per digit)
    pop ax          ; Restore AX from stack
    ret

set_text_color:
    push ax
    push bx
    mov ah, 0x09 
    int 0x10
    pop bx
    pop ax
    ret

section .data
panic_msg db 'Kernel Panic:', 0
error_msg db ' Error code: 0x', 0

section .bss
error_code resd 1
