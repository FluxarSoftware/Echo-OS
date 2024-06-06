ENTRY(start)

SECTIONS
{
    /* Multiboot Header */
    . = 1M;
    .mboot : AT(ADDR(.mboot) - 1M)
    {
        *(.multiboot_header) 
    }

    /* Code */
    .text : {
        *(.text*)
    }

    /* Read-Only Data */
    .rodata : {
        *(.rodata*)
    }

    /* Initialized Data */
    .data : {
        *(.data*)
    }

    /* Uninitialized Data (BSS) */
    .bss : {
        *(COMMON)
        *(.bss*)
    }
}
