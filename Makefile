CC = gcc

IMAGE = kfs

CFLAGS = -Wall -Wextra -Werror -m32 -ffreestanding -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs

BOOT_OBJ = boot.o

BOOT_FILE = boot.s

OBJ_DIR = objs

KERNEL_FILES = kernel_main.c \
				terminal.c \
				lic/strlen.c

SRC_DIR = src/

KERNEL_SRC = $(addprefix $(SRC_DIR), $(KERNEL_FILES))

KERNEL_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(KERNEL_SRC))

build: $(BOOT_OBJ) $(KERNEL_OBJS)

$(BOOT_OBJ): $(BOOT_FILE)
	@nasm -f elf32 boot.s -o boot.o

# %.o: %.c
# 	$(CC) -m32 $(CFLAGS) -c $< -o $@
# 	mv $@ objs/$@

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(IMAGE): $(BOOT_OBJ) $(KERNEL_OBJS)
	@$(CC) -m32 -T linker.ld -o isodir/boot/kfs -ffreestanding -O2 -nostdlib boot.o $(KERNEL_OBJS)

link: $(IMAGE)

run:
	docker run --rm -v $(shell pwd):/root/env kfs-builder bash -c "make link && grub-mkrescue -o kfs.iso isodir"

fclean:
# 	@rm -f $(BOOT_OBJ)
# 	@rm -f $(KERNEL_OBJS)
# 	@rm -f $(IMAGE)
# 	@rm -f isodir/boot/kfs
# 	@rm -f kfs.iso
# 	@echo FCleaned

re: fclean link run
