#pragma once

typedef struct {
	int	alt;
	int	ctrl;
	int rshift;
	int lshift;
	int capslock;
	int numlock;
} kbd_opt_t;

#define KBD_ESC 27

#define KBD_LSHIFT 0x80
#define KBD_RSHIFT 0x81
#define KBD_LCTRL 0x82
#define KBD_LALT 0x83

#define KBD_CAPSLOCK 0x90
#define KBD_NUMLOCK 0x91
#define KBD_SCROLLLOCK 0x92

#define KBD_F1 0xA1
#define KBD_F2 0xA2
#define KBD_F3 0xA3
#define KBD_F4 0xA4
#define KBD_F5 0xA5
#define KBD_F6 0xA6
#define KBD_F7 0xA7
#define KBD_F8 0xA8
#define KBD_F9 0xA9
#define KBD_F10 0xAA
#define KBD_F11 0xAB
#define KBD_F12 0xAC

#define KBD_KP_0 0xB0
#define KBD_KP_1 0xB1
#define KBD_KP_2 0xB2
#define KBD_KP_3 0xB3
#define KBD_KP_4 0xB4
#define KBD_KP_5 0xB5
#define KBD_KP_6 0xB6
#define KBD_KP_7 0xB7
#define KBD_KP_8 0xB8
#define KBD_KP_9 0xB9
#define KBD_KP_DOT 0xBA
#define KBD_KP_ENTER 0xBB
#define KBD_KP_PLUS 0xBC
#define KBD_KP_MINUS 0xBD
#define KBD_KP_MULTIPLY 0xBE
#define KBD_KP_DIVIDE 0xBF