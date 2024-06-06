global start 
extern long_mode_start

section .text
bits 32

start:
    mov esp, stack_top

    call check_multiboot
    call check_cpuid
    call check_long_mode

    call setup_page_tables
    call enable_paging

    lgdt [gdt64.pointer]
    jmp gdt64.code_segment:long_mode_start

    hlt

%include "src/impl/x86_64/boot/cpu/multiboot.asm"
%include "src/impl/x86_64/boot/cpu/cpuid.asm"
%include "src/impl/x86_64/boot/cpu/long_mode.asm"
%include "src/impl/x86_64/boot/memory/paging.asm"
%include "src/impl/x86_64/boot/memory/disk.asm"
%include "src/impl/x86_64/boot/utils/print.asm"
%include "src/impl/x86_64/boot/utils/error.asm"

section .bss
stack_bottom: resb 4096 * 4
stack_top:

section .rodata
gdt64:
    dq 0
.code_segment equ $ - gdt64
    dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53)
.pointer:
    dw $ - gdt64 - 1
    dq gdt64
