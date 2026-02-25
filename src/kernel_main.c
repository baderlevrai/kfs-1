#include "kernel.h"

void	hello(void) {
	terminal_wstr("   _____ ________\n");
	terminal_wstr("  /  |  |\\_____  \\\n");
	terminal_wstr(" /   |  |_/  ____/\n");
	terminal_wstr("/    ^   /       \\\n");
	terminal_wstr("\\____   |\\_______ \\\n");
	terminal_wstr("     |__|        \\/\n");
}

uint8_t	read_keyboard(void) {
	while (!(inb(KEYBOARD_STATUS_PORT) & 1)) {}

	return inb(KEYBOARD_DATA_PORT);
}

// Table de correspondance pour le Set 1
unsigned char kbd_map[128] = {
	0, 27, '1', '2','3', '4','5', '6','7', '8',
	'9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', KBD_LCTRL,
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
	'\'', '`', KBD_LSHIFT, '\\', 'z', 'x', 'c', 'v', 'b', 'n',
	'm', ',', '.', '/', KBD_RSHIFT, KBD_KP_MULTIPLY, KBD_LALT, ' ', KBD_CAPSLOCK, KBD_F1,
	KBD_F2, KBD_F3, KBD_F4, KBD_F5, KBD_F6, KBD_F7, KBD_F8, KBD_F9, KBD_F10, KBD_NUMLOCK,
	KBD_SCROLLLOCK, KBD_KP_7, KBD_KP_8, KBD_KP_9, KBD_KP_MINUS, KBD_KP_4, KBD_KP_5, KBD_KP_6, KBD_KP_PLUS, KBD_KP_1,
	KBD_KP_2, KBD_KP_3, KBD_KP_0, KBD_KP_DOT, 0, 0, 0, KBD_F11, KBD_F12, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

void kernel_main(void)
{
	terminal_initialize();

	terminal_wstr("Hello, kernel World!\n");
	terminal_wstr("This is a simple kernel written in C.\n");

	// hello();

	while (1)
	{
		uint8_t scancode = read_keyboard();

		//Extended keys
		if (scancode == 0xE0 || scancode == 0xE1) {
			continue;
		}

		if (scancode & 0x80) {
			uint8_t key_release = scancode & 0x7F;
			terminal_wstr("Key released: ");
			terminal_wchar(kbd_map[key_release]);
			terminal_wchar('\n');
		} else {
			terminal_wstr("Key pressed: ");
			terminal_wchar(kbd_map[scancode]);
			terminal_wchar('\n');
		}

	}

}
