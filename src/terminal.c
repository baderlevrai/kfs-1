#include "kernel.h"

size_t		terminal_row;
size_t		terminal_column;
uint8_t		terminal_color;
uint16_t*	terminal_buffer = (uint16_t*)VGA_MEMORY;

uint8_t		curr_tty = 0;
uint16_t	ttys[2][VGA_HEIGHT * VGA_WIDTH];
size_t		ttys_cursor[2][2] = { 0 };

inline uint8_t	vga_entry_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}

inline uint16_t	vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	outb(VGA_CTRL_REGISTER, 0x0F);
	outb(VGA_DATA_REGISTER, (uint8_t) (pos & 0xFF));

	outb(VGA_CTRL_REGISTER, 0x0E);
	outb(VGA_DATA_REGISTER, (uint8_t) ((pos >> 8) & 0xFF));
}

void terminal_initialize(void)
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_MAGENTA);

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
			ttys[0][index] = terminal_buffer[index];
			ttys[1][index] = terminal_buffer[index];
		}
	}
}

void terminal_scroll_down()
{
  for (size_t i = 1; i < VGA_HEIGHT; i++) {
    for (size_t j = 0; j < VGA_WIDTH; j++) {
		const size_t index = i * VGA_WIDTH + j;
    	terminal_buffer[index - VGA_WIDTH] = terminal_buffer[index];
    	ttys[curr_tty][index - VGA_WIDTH] = terminal_buffer[index - VGA_WIDTH];
    }
  }
  for (size_t j = 0; j < VGA_WIDTH; j++) {
    const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + j;
    terminal_buffer[index] = vga_entry(' ', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_MAGENTA));
    ttys[curr_tty][index] = vga_entry(' ', vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_MAGENTA));
  }
  terminal_column = 0;
  terminal_row--;
  update_cursor(terminal_column, terminal_row);
}


void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
	ttys[curr_tty][index] = terminal_buffer[index];
}

void terminal_putchar(char c)
{
	if (c == '\n') {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_scroll_down();
		return;
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
      terminal_scroll_down();
	}
}

void terminal_write(const char* data, size_t size)
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_wchar(char c)
{
	terminal_putchar(c);
	update_cursor(terminal_column, terminal_row);
}

void terminal_wstr(const char* data)
{
	terminal_write(data, strlen(data));
	update_cursor(terminal_column, terminal_row);
}

void change_tty(uint8_t tty)
{
	ttys_cursor[curr_tty][0] = terminal_row;
	ttys_cursor[curr_tty][1] = terminal_column;
	curr_tty = tty;
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_MAGENTA);

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = ttys[tty][index];
		}
	}
	terminal_row = ttys_cursor[curr_tty][0];
	terminal_column = ttys_cursor[curr_tty][1];
	update_cursor(terminal_column, terminal_row);
}
