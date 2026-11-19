ENTRY(_start)

SECTIONS
{
    /*place the kernel at 1 MB — above the BIOS/VGA memory below it*/
    . = 1M;
    /* multiboot header is first so GRUB finds it when scanning */
    .multiboot : { *(.multiboot) }
    /* code: all functions' instructions, from object file */
    .text      : { *(.text)      }
    /* read-only data: string literals */
    .rodata    : { *(.rodata)    }
    /*initialized global/static variables*/
    .data      : { *(.data)      }
    /*uninitialized/reserved memory | where the stack lives*/
    .bss       : { *(.bss)       }
}