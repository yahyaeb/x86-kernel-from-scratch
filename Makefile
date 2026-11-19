# ---- Tools ----
ASM     = nasm
CC      = gcc
LD      = ld

# ---- Flags ----
ASMFLAGS = -f elf32
CFLAGS   = -m32 -ffreestanding -fno-stack-protector -fno-builtin 
LDFLAGS  = -m elf_i386 -T linker.ld

# ---- Files ----
NAME    = kernel.bin
OBJS    = boot.o kmain.o lib.o

# ---- Default target ----
all: $(NAME)

# Link all objects into the kernel binary
$(NAME): $(OBJS) linker.ld
	$(LD) $(LDFLAGS) -o $(NAME) $(OBJS)

# Assemble .asm -> .o
boot.o: boot.asm
	$(ASM) $(ASMFLAGS) boot.asm -o boot.o

# Compile .c -> .o
kmain.o: kmain.c
	$(CC) $(CFLAGS) -c kmain.c -o kmain.o

# Iso build
iso: $(NAME)
	cp $(NAME) iso/boot/
	grub-mkrescue -o kfs.iso iso

# Boot it in QEMU (test shortcut)
run: $(NAME)
	qemu-system-i386 -kernel $(NAME)

lib.o: lib.c
	$(CC) $(CFLAGS) -c lib.c -o lib.o

# Remove object files
clean:
	rm -f $(OBJS)

# Remove everything built
fclean: clean
	rm -f $(NAME) kfs.iso iso/boot/kernel.bin

# Rebuild from scratch
re: fclean all

.PHONY: all run iso clean fclean re