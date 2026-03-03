# Kernel From Scratch (KFS-1)

## Description

This project goal is to create our first kernel that is bootable with grub. This kernel is written in C and Assembly.

Currently this kernel handles multiple screens, keyboard input and colors.

## Instructions

Compiling this kernel requires Docker, and running it requires QEMU.

1. Clone the repository:

```bash
git clone git@github.com:baderlevrai/kfs-1.git
cd kfs-1
```

2. Build the container:

```bash
docker build . -t kfs-builder
```

3. Build the iso and run it:
```bash
make && make run
```

## Resources

- [📖 Kernel Bible](https://wiki.osdev.org/)
- [🖥️ VGA](https://web.stanford.edu/class/cs140/projects/pintos/specs/freevga/vga/crtcreg.htm#0C)