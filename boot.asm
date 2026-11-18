bits 32

section .multiboot
; dd = define doubleword = 4 bytes (32 bits); each multiboot field is 32 bits.
align 4                    ; multiboot spec requires the header 4-byte aligned
    dd 0x1BADB002          ; magic: fixed value GRUB scans for to recognize a multiboot kernel
    dd 0x0                 ; flags: request no extra features (simple "42" kernel)
    dd -(0x1BADB002 + 0x0) ; checksum: makes magic+flags+checksum == 0, proving the header is genuine

; #-----#

section .bss               ; reserved, uninitialized memory (no starting values)
align 16                   ; x86 ABI requires the stack 16-byte aligned for function calls
stack_bottom:
    resb 16384             ; reserve 16 KB of stack space
stack_top:

section .text              ; executable code goes here (switch from reserving memory to code)
global _start              ; make the _start symbol visible to the linker (our entry point)
extern kmain               ; kmain is defined in another file (our C); linker will connect it

_start:
    mov esp, stack_top     ; point the stack pointer at the top of our stack
    call kmain             ; jump into our C code

    cli                    ; disable interrupts (reached only if kmain returns; no OS to return to)
.hang:                     ; label for the halt loop
    hlt                    ; halt the CPU until an interrupt (none, since cli)
    jmp .hang              ; if ever woken, halt again — freeze forever, never run into garbage