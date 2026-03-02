#include <kernel.h>
#include "keyboard.h"

// Table de correspondance pour le Set 1
unsigned char kbd_map[128] = {
    [0x01] = KBD_ESC,    [0x02] = '1',      [0x03] = '2',      [0x04] = '3',
    [0x05] = '4',        [0x06] = '5',      [0x07] = '6',      [0x08] = '7',
    [0x09] = '8',        [0x0A] = '9',      [0x0B] = '0',      [0x0C] = '-',
    [0x0D] = '=',        [0x0E] = '\b',     [0x0F] = '\t',     [0x10] = 'q',
    [0x11] = 'w',        [0x12] = 'e',      [0x13] = 'r',      [0x14] = 't',
    [0x15] = 'y',        [0x16] = 'u',      [0x17] = 'i',      [0x18] = 'o',
    [0x19] = 'p',        [0x1A] = '[',      [0x1B] = ']',      [0x1C] = '\n',
    [0x1D] = KBD_LCTRL,  [0x1E] = 'a',      [0x1F] = 's',      [0x20] = 'd',
    [0x21] = 'f',        [0x22] = 'g',      [0x23] = 'h',      [0x24] = 'j',
    [0x25] = 'k',        [0x26] = 'l',      [0x27] = ';',      [0x28] = '\'',
    [0x29] = '`',        [0x2A] = KBD_LSHIFT, [0x2B] = '\\',   [0x2C] = 'z',
    [0x2D] = 'x',        [0x2E] = 'c',      [0x2F] = 'v',      [0x30] = 'b',
    [0x31] = 'n',        [0x32] = 'm',      [0x33] = ',',      [0x34] = '.',
    [0x35] = '/',        [0x36] = KBD_RSHIFT, [0x37] = KBD_KP_MULTIPLY,
    [0x38] = KBD_LALT,   [0x39] = ' ',      [0x3A] = KBD_CAPSLOCK,
    
    [0x3B] = KBD_F1,     [0x3C] = KBD_F2,   [0x3D] = KBD_F3,   [0x3E] = KBD_F4,
    [0x3F] = KBD_F5,     [0x40] = KBD_F6,   [0x41] = KBD_F7,   [0x42] = KBD_F8,
    [0x43] = KBD_F9,     [0x44] = KBD_F10,

    [0x45] = KBD_NUMLOCK, [0x46] = KBD_SCROLLLOCK,
    [0x47] = KBD_KP_7,    [0x48] = KBD_KP_8, [0x49] = KBD_KP_9, [0x4A] = KBD_KP_MINUS,
    [0x4B] = KBD_KP_4,    [0x4C] = KBD_KP_5, [0x4D] = KBD_KP_6, [0x4E] = KBD_KP_PLUS,
    [0x4F] = KBD_KP_1,    [0x50] = KBD_KP_2, [0x51] = KBD_KP_3, [0x52] = KBD_KP_0,
    [0x53] = KBD_KP_DOT,

    [0x57] = KBD_F11,    [0x58] = KBD_F12
};

unsigned char numpad_map[16] = {
    [KBD_KP_0 & 0x0F] = '0',
    [KBD_KP_1 & 0x0F] = '1',
    [KBD_KP_2 & 0x0F] = '2',
    [KBD_KP_3 & 0x0F] = '3',
    [KBD_KP_4 & 0x0F] = '4',
    [KBD_KP_5 & 0x0F] = '5',
    [KBD_KP_6 & 0x0F] = '6',
    [KBD_KP_7 & 0x0F] = '7',
    [KBD_KP_8 & 0x0F] = '8',
    [KBD_KP_9 & 0x0F] = '9',
    [KBD_KP_DOT & 0x0F]      = '.',
    [KBD_KP_ENTER & 0x0F]    = '\n',
    [KBD_KP_PLUS & 0x0F]     = '+',
    [KBD_KP_MINUS & 0x0F]    = '-',
    [KBD_KP_MULTIPLY & 0x0F] = '*',
    [KBD_KP_DIVIDE & 0x0F] = '/'
};

const char* special_key_names[] = {
    [KBD_LSHIFT & 0x3F] = "Left Shift", [KBD_RSHIFT & 0x3F] = "Right Shift", [KBD_LCTRL & 0x3F] = "Left Ctrl", [KBD_LALT & 0x3F] = "Left Alt",
    [KBD_CAPSLOCK & 0x3F] = "Capslock", [KBD_NUMLOCK & 0x3F] = "Numlock", [KBD_SCROLLLOCK & 0x3F] = "Scroll Lock",
    
    [KBD_F1 & 0x3F] = "F1", [KBD_F2 & 0x3F] = "F2", [KBD_F3 & 0x3F] = "F3", [KBD_F4 & 0x3F] = "F4",
    [KBD_F5 & 0x3F] = "F5", [KBD_F6 & 0x3F] = "F6", [KBD_F7 & 0x3F] = "F7", [KBD_F8 & 0x3F] = "F8", 
    [KBD_F9 & 0x3F] = "F9", [KBD_F10 & 0x3F] = "F10", [KBD_F11 & 0x3F] = "F11", [KBD_F12 & 0x3F] = "F12",
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

int is_no_ascii(unsigned char key) {
    return key >= 128; //0x80
}

void    no_ascii_handler(unsigned char key) {
    unsigned char index = key & 0x3F;

    if (is_numpad(key)) {
        kbd_numpad_handler(key);
        return;
    }

    terminal_wstr(special_key_names[index]);
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
			} else if (key == KBD_LCTRL) {
				options.ctrl = 1;
			} else if (key == KBD_CAPSLOCK) {
				options.capslock = !options.capslock;
			} else if (key == KBD_NUMLOCK) {
				options.numlock = !options.numlock; 
			} else if (key == KBD_LSHIFT) {
				options.lshift = 1;
			} else if (key == KBD_RSHIFT) {
				options.rshift = 1;
			}

            if (is_no_ascii(key)) {
                no_ascii_handler(key);
            } else {
                terminal_wchar(key);
            }

			if (key == KBD_F1 || key == KBD_F2)
				change_tty((key == KBD_F2));
		}
	}
}