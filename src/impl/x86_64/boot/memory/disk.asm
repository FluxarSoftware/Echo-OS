global disk_read
extern error

section .text
bits 32

disk_read:
    ; Arguments:
    ;   bx: Buffer to store data
    ;   chs (cylinder, head, sector) in cx, dh, dl respectively
    ;   eax: Number of sectors to read
    pusha

    mov ah, 0x02
    mov al, [eax]
    int 0x13
    jc .disk_error
    popa
    ret

.disk_error:
    mov eax, "D"
    call error
