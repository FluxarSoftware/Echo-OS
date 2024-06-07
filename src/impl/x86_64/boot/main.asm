section .text
global start, error
extern check_multiboot, check_cpuid, check_long_mode, long_mode_start

section .text
bits 32
start:
    mov esp, stack_top

    call check_multiboot
    call check_cpuid
    call check_long_mode

    call setup_gdt

    call setup_page_tables
    call enable_paging

    lgdt [gdt64.pointer]
    jmp gdt64.code_segment:long_mode_start

    hlt

setup_gdt:
    ; Null descriptor
    mov word [gdt + 0], 0
    mov dword [gdt + 2], 0

    ; Kernel code segment
    mov word [gdt + 8], 0xFFFF    ; Limit (Low)
    mov word [gdt + 10], 0x00    ; Base (Low)
    mov byte [gdt + 12], 0x9A     ; Access byte (P=1, DPL=0, S=1, Type=1010b)
    mov byte [gdt + 13], 0xCF     ; Flags (G=1, D=1, L=0)
    mov byte [gdt + 14], 0x00    ; Base (Middle)
    mov dword [gdt + 15], 0x00   ; Base (High), Limit (High)

    ; Kernel data segment
    mov word [gdt + 24], 0xFFFF    ; Limit (Low)
    mov word [gdt + 26], 0x00    ; Base (Low)
    mov byte [gdt + 28], 0x92     ; Access byte (P=1, DPL=0, S=1, Type=0010b)
    mov byte [gdt + 29], 0xCF     ; Flags (G=1, D=1, L=0)
    mov byte [gdt + 30], 0x00    ; Base (Middle)
    mov dword [gdt + 31], 0x00   ; Base (High), Limit (High)

    ; User code segment
    mov word [gdt + 40], 0xFFFF    ; Limit (Low)
    mov word [gdt + 42], 0x00    ; Base (Low)
    mov byte [gdt + 44], 0xFA     ; Access byte (P=1, DPL=3, S=1, Type=1010b)
    mov byte [gdt + 45], 0xCF     ; Flags (G=1, D=1, L=0)
    mov byte [gdt + 46], 0x00    ; Base (Middle)
    mov dword [gdt + 47], 0x00   ; Base (High), Limit (High)

    ; User data segment
    mov word [gdt + 56], 0xFFFF    ; Limit (Low)
    mov word [gdt + 58], 0x00    ; Base (Low)
    mov byte [gdt + 60], 0xF2     ; Access byte (P=1, DPL=3, S=1, Type=0010b)
    mov byte [gdt + 61], 0xCF     ; Flags (G=1, D=1, L=0)
    mov byte [gdt + 62], 0x00    ; Base (Middle)
    mov dword [gdt + 63], 0x00   ; Base (High), Limit (High)

    lgdt [gdtr]
    ret

gdt:
    ; GDT entries will be stored here
    times 64 resb 1
gdtr:
    dw 80h - 1
    dd gdt

setup_page_tables:
    mov eax, page_table_l3
    or eax, 0b11
    mov [page_table_l4], eax

    mov eax, page_table_l2
    or eax, 0b11
    mov [page_table_l3], eax

    mov ecx, 0
.loop:
    mov eax, 0x200000
    mul ecx
    or eax, 0b10000011
    mov [page_table_l2 + ecx * 8], eax

    inc ecx,
    cmp ecx, 512
    jne .loop

    ret

enable_paging:
    mov eax, page_table_l4
    mov cr3, eax

    ; enable PAE
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; enable long mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ret

error:
    mov dword [0xb8000], 0x4f524f45
    mov dword [0xb8004], 0x4f3a4f52
    mov dword [0xb8008], 0x4f204f20
    mov byte [0xb800a], al
    hlt

section .bss
align 4096
page_table_l4: resb 4096
page_table_l3: resb 4096
page_table_l2: resb 4096
stack_bottom:
    resb 4096 * 4
stack_top:

section .rodata
gdt64:
  dq 0 ; zero entry
.code_segment: equ $ - gdt64
  dq (1 << 43) | (1 << 44) | (1 << 47) | (1 << 53)
.pointer:
  dw $ - gdt64 - 1
  dq gdt64
