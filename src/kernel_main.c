#include "kernel.h"

// void	enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
// 	outb(0x3D4, 0x0A);
// 	outb(0x3D5, (inb(0x3D5) & 0x0C0) | cursor_start);

// 	outb(0x3D4, 0x0B);
// 	outb(0x3D5, (inb(0x3D5) & 0x0C0) | cursor_end);
// }

void	hello(void) {
	terminal_wstr("   _____ ________\n");
	terminal_wstr("  /  |  |\\_____  \\\n");
	terminal_wstr(" /   |  |_/  ____/\n");
	terminal_wstr("/    ^   /       \\\n");
	terminal_wstr("\\____   |\\ \\\n");
	terminal_wstr("     |__|        \\/\n");
}

void kernel_main(void)
{
	terminal_initialize();

	terminal_wstr("Hello, kernel World!\n");
	terminal_wstr("This is a simple kernel written in C.\n");

	hello();
}
