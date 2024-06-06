section .data
    hex_chars db "0123456789ABCDEF" ; Array of hexadecimal characters
    
section .text
    global print_hex
    
print_hex:
    push rbp
    mov rbp, rsp
    
    ; Save registers
    push rbx
    push rcx
    push rdx
    
    ; Initialize variables
    mov rsi, hex_chars ; Pointer to the hex character array
    mov rcx, 16 ; Counter for the number of digits (64-bit integer)
    
    mov rax, rdi ; Copy the input value to rax
    
hex_loop:
    mov rbx, rax ; Copy rax to rbx for manipulation
    and rbx, 0xF ; Mask out all but the lowest 4 bits
    movzx rbx, byte [rsi + rbx] ; Load the corresponding hex character
    
    ; Print the character
    mov rdx, 1 ; File descriptor for stdout
    mov rsi, rbx ; Address of the character to print
    mov rdi, 1 ; Length of the string to print
    mov rax, 1 ; syscall number for write
    syscall
    
    shr rax, 4 ; Shift right by 4 bits to process the next hex digit
    loop hex_loop ; Repeat until all digits are processed
    
    ; Restore registers
    pop rdx
    pop rcx
    pop rbx
    
    ; Clean up and return
    pop rbp
    ret
