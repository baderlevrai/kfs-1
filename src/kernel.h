#pragma once

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

typedef unsigned char		uint8_t;
typedef unsigned short int	uint16_t;
typedef unsigned int		uint32_t;
typedef unsigned long		size_t;

#define VGA_WIDTH	80
#define VGA_HEIGHT	25
#define VGA_MEMORY	0xB8000

#define VGA_CTRL_REGISTER 0x3D4
#define VGA_DATA_REGISTER 0x3D5
#define CURSOR_END_INDEX  0x0B

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

#define KBD_ESC 27

#define KBD_LSHIFT 0x71
#define KBD_RSHIFT 0x72
#define KBD_LCTRL 0x73
#define KBD_LALT 0x74

#define KBD_CAPSLOCK 0x75
#define KBD_NUMLOCK 0x76
#define KBD_SCROLLLOCK 0x77

#define KBD_F1 0x91
#define KBD_F2 0x92
#define KBD_F3 0x93
#define KBD_F4 0x94
#define KBD_F5 0x95
#define KBD_F6 0x96
#define KBD_F7 0x97
#define KBD_F8 0x98
#define KBD_F9 0x99
#define KBD_F10 0x9A
#define KBD_F11 0x9B
#define KBD_F12 0x9C

#define KBD_KP_0 0x80
#define KBD_KP_1 0x81
#define KBD_KP_2 0x82
#define KBD_KP_3 0x83
#define KBD_KP_4 0x84
#define KBD_KP_5 0x85
#define KBD_KP_6 0x86
#define KBD_KP_7 0x87
#define KBD_KP_8 0x88
#define KBD_KP_9 0x89
#define KBD_KP_DOT 0x8A
// #define KBD_KP_ENTER 0x0B
#define KBD_KP_PLUS 0x8C
#define KBD_KP_MINUS 0x8D
#define KBD_KP_MULTIPLY 0x8E

void	terminal_initialize(void);
void	terminal_wstr(const char* data);
void	terminal_wchar(char c);
size_t	strlen(const char* str);

void	kbd_handler(void);
void	kbd_init(void);

inline void outb(uint16_t port, uint8_t val)
{
	asm volatile ("outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

inline uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile ( "inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}
