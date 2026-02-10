BOOT = boot.bin

BOOT_FILE = boot.s

build: $(BOOT)

$(BOOT): $(BOOT_FILE)
	nasm -f elf32 boot.s -o boot.o
	ld -m elf_i386 -o boot.bin --oformat binary -e init boot.o