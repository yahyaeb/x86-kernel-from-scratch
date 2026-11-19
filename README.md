# x86 Kernel From Scratch

A minimal 32-bit (i386) operating-system kernel that boots on bare metal via GRUB, written from scratch in C and x86 assembly. Built to understand how a computer goes from power-on to running your own code — with no operating system, no standard library, and no training wheels underneath.

## What it does

The kernel boots through GRUB, sets up its own stack, and writes directly to VGA text memory to display output on screen — a banner and text, rendered by a small I/O interface built from scratch.

## Features

- **Multiboot-compliant boot** — a hand-written multiboot header so GRUB recognizes and loads the kernel
- **Freestanding C** — compiled with no standard library and no OS underneath (`-ffreestanding`, `-nostdlib`)
- **Custom linker script** — lays the kernel out in memory (loaded at 1 MB, multiboot header first)
- **VGA text driver** — writes directly to video memory at `0xB8000`; supports `putchar`, `putstr`, `putnbr`, screen clearing, and cursor tracking
- **Minimal kernel library** — hand-written `strlen`, `strcmp`, `memset` and fixed-width types, since there is no libc
- **Reproducible build** — a Docker-based build produces a bootable ISO with no host dependencies

## How it works

```
Power on → BIOS → GRUB → (validates multiboot header, loads kernel at 1 MB,
switches CPU to 32-bit) → boot.asm (sets up stack, calls kmain) →
kmain writes to VGA memory → output appears on screen
```

Three sources are compiled and linked into one bootable binary:

| File         | Role                                                        |
|--------------|-------------------------------------------------------------|
| `boot.asm`   | Multiboot header, stack setup, entry point (`_start`)       |
| `kmain.c`    | Kernel entry point and VGA screen interface                 |
| `lib.c`      | Freestanding helper functions (`strlen`, `strcmp`, `memset`)|
| `linker.ld`  | Memory layout: entry point, 1 MB load address, section order|

## Build & run

### Quick test (needs a Linux host with `nasm`, `gcc`, `qemu`)

```bash
make            # build kernel.bin
make run        # boot it directly in QEMU
```

### Full bootable ISO (via Docker — no host tools needed)

```bash
./build.sh      # builds the ISO inside a container, then boots it in QEMU
```

The ISO boots through real GRUB, exactly as it would on physical hardware.

## Tech stack

- **Languages:** C, x86 assembly (NASM)
- **Toolchain:** GCC (`-m32`), GNU `ld`, GRUB, QEMU
- **Build:** GNU Make, Docker (reproducible build)
- **Architecture:** i386 (32-bit x86), legacy BIOS + Multiboot

## What I learned

- The x86 boot process from power-on through to running custom code
- The Multiboot protocol and how bootloaders hand off to a kernel
- Writing freestanding C with no OS or standard library
- Linker scripts and controlling memory layout
- Memory-mapped I/O (writing directly to VGA hardware)
- Cross-compilation and packaging a reproducible, bootable image