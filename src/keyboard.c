#include "kernel.h"
#include "keyboard.h"

// Table de correspondance pour le Set 1
unsigned char kbd_map[128] = {
	0, KBD_ESC, '1', '2','3', '4','5', '6','7', '8',
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

unsigned char	numpad_map[16] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'.', '\n', '+', '-', '*'
};

kbd_opt_t options;

uint8_t	read_keyboard(void) {
	while (!(inb(KEYBOARD_STATUS_PORT) & 1)) {}

	return inb(KEYBOARD_DATA_PORT);
}

void	kbd_init(void) {
	options.alt = 0;
	options.ctrl = 0;
	options.rshift = 0;
	options.lshift = 0;
	options.capslock = 0;
	options.numlock = 0;
}

void	kbd_numpad_handler(unsigned char key) {
	if (!options.numlock) return;

	uint8_t np_key = key & 0x0F;

	terminal_wchar(numpad_map[np_key]);
}

int	is_numpad(unsigned char key) {
	return key >= KBD_KP_0 && key <= KBD_KP_MULTIPLY;
}

void	kbd_handler(void) {
	int is_extended = 0;

	while (1) {
		uint8_t scancode = read_keyboard();

		if (scancode == 0xE0 || scancode == 0xE1) {
			is_extended = 1;
			continue;
		}

		if (is_extended) {
			is_extended = 0;
			continue;
		}

		if (scancode & 0x80) { //Released

			uint8_t key_release = scancode & 0x7F;
			unsigned char key = kbd_map[key_release];

			if (key == KBD_LALT) {
				options.alt = 0;
			} else if (key == KBD_LCTRL) {
				options.ctrl = 0;
			} else if (key == KBD_LSHIFT) {
				options.lshift = 0;
			} else if (key == KBD_RSHIFT) {
				options.rshift = 0;
			}

		} else { //Pressed
			unsigned char key = kbd_map[scancode];

			if (key == KBD_LALT) {
				options.alt = 1;
				terminal_wstr("alt pressed\n");
			} else if (key == KBD_LCTRL) {
				options.ctrl = 1;
				terminal_wstr("Left Control pressed\n");
			} else if (key == KBD_CAPSLOCK) {
				options.capslock = options.numlock ? 0 : 1;
				terminal_wstr("Capslock pressed\n");
			} else if (key == KBD_NUMLOCK) {
				options.numlock = options.numlock ? 0 : 1; 
				terminal_wstr("Numlock pressed\n");
			} else if (key == KBD_LSHIFT) {
				options.lshift = 1;
				terminal_wstr("Left Shift pressed\n");
			} else if (key == KBD_RSHIFT) {
				options.rshift = 1;
				terminal_wstr("Right Shift pressed\n");
			} else if (is_numpad(key)) {
				kbd_numpad_handler(key);
			} else {
				terminal_wchar(key);
			}
		}
	}
}