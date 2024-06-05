#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

char get_input_keycode();
char get_ascii_char(uint8_t keycode);

#endif
