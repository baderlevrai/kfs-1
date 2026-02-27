CC = gcc

IMAGE_DIR = isodir
IMAGE = $(IMAGE_DIR)/boot/kfs

ISO = kfs.iso

CFLAGS = -Wall -Wextra -Werror -m32 -ffreestanding -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs -O2 -Isrc 

BOOT_OBJ = boot.o

BOOT_FILE = boot.s

OBJ_DIR = objs

KERNEL_FILES = kernel_main.c \
				terminal.c \
				strlen.c \
				keyboard.c \
				printk.c

SRC_DIR = src/

KERNEL_SRC = $(addprefix $(SRC_DIR), $(KERNEL_FILES))

KERNEL_OBJS = $(KERNEL_SRC:.c=.o)

all: $(ISO) 

$(ISO): $(IMAGE)
	@make build-iso --no-print-directory

build: $(BOOT_OBJ) $(KERNEL_OBJS)
	echo $(KERNEL_OBJS)

$(BOOT_OBJ): $(BOOT_FILE)
	@docker run --rm -v $(shell pwd):/root/env kfs-builder bash -c "nasm -f elf32 $(BOOT_FILE) -o $(BOOT_OBJ)"
	@echo Boot file created.

%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(IMAGE): $(BOOT_OBJ) $(KERNEL_OBJS)
	@$(CC) $(CFLAGS) -T linker.ld -o $(IMAGE) -ffreestanding -O2 -nostdlib $(BOOT_OBJ) $(KERNEL_OBJS)
	@echo Image created.

link: $(IMAGE)

build-iso: $(IMAGE)
	@docker run --rm -v $(shell pwd):/root/env kfs-builder bash -c "grub-mkrescue -o $(ISO) $(IMAGE_DIR)"
	@echo Iso created.

run: $(ISO)
	@qemu-system-x86_64 $(ISO)

fclean:
	@rm -f $(BOOT_OBJ)
	@rm -f $(KERNEL_OBJS)
	@rm -f $(IMAGE)
	@rm -f $(ISO)
	@echo FCleaned

re: fclean link run
