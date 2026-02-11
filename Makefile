BOOT_OBJ = boot.o

BOOT_FILE = boot.s

build: $(BOOT_OBJ)

$(BOOT_OBJ): $(BOOT_FILE)
	nasm -felf32 boot.s -o boot.o
# 	ld -m elf_i386 -o boot.bin --oformat binary -e init boot.o

fclean:
	rm $(BOOT_OBJ)