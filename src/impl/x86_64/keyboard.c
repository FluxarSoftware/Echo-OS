#include "keyboard.h"
#include "print.h"
#include "port.h"

// PS/2 Keyboard Ports
#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

static int is_shift_pressed = 0;
static int is_caps_lock_on = 0;
static char input_buffer[256];
static int buffer_index = 0;

char get_input_keycode() {
    while ((port_byte_in(KEYBOARD_STATUS_PORT) & 0x01) == 0);
    return port_byte_in(KEYBOARD_DATA_PORT);
}
void handle_backspace() {
    if (buffer_index > 0) {
        buffer_index--;
        input_buffer[buffer_index] = '\0';
        print_char('\b');
        print_char(' ');
        print_char('\b');
    }
}
char get_ascii_char(uint8_t keycode) {
    switch (keycode) {
        case 0x2A:
        case 0x36:
            is_shift_pressed = 1;
            return 0;
        case 0xAA:
        case 0xB6:
            is_shift_pressed = 0;
            return 0;
        case 0x3A:
            is_caps_lock_on = !is_caps_lock_on;
            return 0;
        case 0x0E: return '\b';
        case 0x1C: return '\n';
        case 0x53: return '\177';
        case 0x0F: return '\t';
        case 0x39: return ' ';
    }
    if (keycode & 0x80) { 
        keycode &= 0x7F;
        if (keycode == 0x2A || keycode == 0x36) {
            is_shift_pressed = 0;
        }
        return 0;
    }
    switch (keycode) {
        case 0x10: return is_shift_pressed ? 'Q' : (is_caps_lock_on ? 'Q' : 'q');
        case 0x11: return is_shift_pressed ? 'W' : (is_caps_lock_on ? 'W' : 'w');
        case 0x12: return is_shift_pressed ? 'E' : (is_caps_lock_on ? 'E' : 'e');
        case 0x13: return is_shift_pressed ? 'R' : (is_caps_lock_on ? 'R' : 'r');
        case 0x14: return is_shift_pressed ? 'T' : (is_caps_lock_on ? 'T' : 't');
        case 0x15: return is_shift_pressed ? 'Y' : (is_caps_lock_on ? 'Y' : 'y');
        case 0x16: return is_shift_pressed ? 'U' : (is_caps_lock_on ? 'U' : 'u');
        case 0x17: return is_shift_pressed ? 'I' : (is_caps_lock_on ? 'I' : 'i');
        case 0x18: return is_shift_pressed ? 'O' : (is_caps_lock_on ? 'O' : 'o');
        case 0x19: return is_shift_pressed ? 'P' : (is_caps_lock_on ? 'P' : 'p');
        case 0x1E: return is_shift_pressed ? 'A' : (is_caps_lock_on ? 'A' : 'a');
        case 0x1F: return is_shift_pressed ? 'S' : (is_caps_lock_on ? 'S' : 's');
        case 0x20: return is_shift_pressed ? 'D' : (is_caps_lock_on ? 'D' : 'd');
        case 0x21: return is_shift_pressed ? 'F' : (is_caps_lock_on ? 'F' : 'f');
        case 0x22: return is_shift_pressed ? 'G' : (is_caps_lock_on ? 'G' : 'g');
        case 0x23: return is_shift_pressed ? 'H' : (is_caps_lock_on ? 'H' : 'h');
        case 0x24: return is_shift_pressed ? 'J' : (is_caps_lock_on ? 'J' : 'j');
        case 0x25: return is_shift_pressed ? 'K' : (is_caps_lock_on ? 'K' : 'k');
        case 0x26: return is_shift_pressed ? 'L' : (is_caps_lock_on ? 'L' : 'l');
        case 0x2C: return is_shift_pressed ? 'Z' : (is_caps_lock_on ? 'Z' : 'z');
        case 0x2D: return is_shift_pressed ? 'X' : (is_caps_lock_on ? 'X' : 'x');
        case 0x2E: return is_shift_pressed ? 'C' : (is_caps_lock_on ? 'C' : 'c');
        case 0x2F: return is_shift_pressed ? 'V' : (is_caps_lock_on ? 'V' : 'v');
        case 0x30: return is_shift_pressed ? 'B' : (is_caps_lock_on ? 'B' : 'b');
        case 0x31: return is_shift_pressed ? 'N' : (is_caps_lock_on ? 'N' : 'n');
        case 0x32: return is_shift_pressed ? 'M' : (is_caps_lock_on ? 'M' : 'm');

        case 0x02: return (is_shift_pressed ? '!' : '1');
        case 0x03: return (is_shift_pressed ? '@' : '2');
        case 0x04: return (is_shift_pressed ? '#' : '3');
        case 0x05: return (is_shift_pressed ? '$' : '4');
        case 0x06: return (is_shift_pressed ? '%' : '5');
        case 0x07: return (is_shift_pressed ? '^' : '6');
        case 0x08: return (is_shift_pressed ? '&' : '7');
        case 0x09: return (is_shift_pressed ? '*' : '8');
        case 0x0A: return (is_shift_pressed ? '(' : '9');
        case 0x0B: return (is_shift_pressed ? ')' : '0');

        case 0x4F: return '1'; case 0x50: return '2';
        case 0x51: return '3'; case 0x4B: return '4';
        case 0x4C: return '5'; case 0x4D: return '6';
        case 0x47: return '7'; case 0x48: return '8';
        case 0x49: return '9'; case 0x52: return '0';

        case 0x4A: return '-'; case 0x4E: return '+';
        case 0x37: return '*';

        case 0x0C: return is_shift_pressed ? '_' : '-';
        case 0x0D: return is_shift_pressed ? '+' : '=';
        case 0x1A: return is_shift_pressed ? '{' : '[';
        case 0x1B: return is_shift_pressed ? '}' : ']';
        case 0x27: return is_shift_pressed ? ':' : ';';
        case 0x28: return is_shift_pressed ? '"' : '\'';
        case 0x29: return is_shift_pressed ? '~' : '`';
        case 0x2B: return is_shift_pressed ? '|' : '\\';
        case 0x33: return is_shift_pressed ? '<' : ',';
        case 0x34: return is_shift_pressed ? '>' : '.';
        case 0x35: return is_shift_pressed ? '?' : '/';

        default:
            print_str("Unhandled scan code: ");
            print_int(keycode, 16);
            print_char(' ');
            return 0; 
    }
    return 0;
}
