#include "kernel.h"

static inline uint8_t	vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

static inline uint16_t	vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

size_t	strlen(const char* str)
{
	size_t len = 0;
	if (!str)
		return 0;
	while (str[len])
		len++;
	return len;
}

size_t		terminal_row;
size_t		terminal_column;
uint8_t		terminal_color;
uint16_t*	terminal_buffer = (uint16_t*)VGA_MEMORY;

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLUE);

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
	if (c == '\n') {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
		return;
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}

void	update_cursor(int x, int y) {
	uint16_t pos = y * VGA_WIDTH + x;

	outb(PORT_TEXT_CURSOR, 0x0F);
}
void terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
	outb(PORT_TEXT_CURSOR, )
}

void terminal_writestring(const char* data)
{
	terminal_write(data, strlen(data));
}

void	hello(void) {
	terminal_writestring("   _____ ________\n");
	terminal_writestring("  /  |  |\\_____  \\\n");
	terminal_writestring(" /   |  |_/  ____/\n");
	terminal_writestring("/    ^   /       \\\n");
	terminal_writestring("\\____   |\\_______ \\\n");
	terminal_writestring("     |__|        \\/\n");
}

void kernel_main(void)
{
	/* Initialize terminal interface */
	terminal_initialize();

	/* Newline support is left as an exercise. */
	terminal_writestring("Hello, kernel World!\n");
	terminal_writestring("This is a simple kernel written in C.\n");

	hello();
}
