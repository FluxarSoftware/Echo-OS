#include "print.h"
#include "keyboard.h"

void kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("Welcome to Echo-OS!\n");
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("\nType something: ");

    char ch = 0;
    do {
        ch = get_input_keycode();
        if (ch) {
            char ascii = get_ascii_char(ch);
            if (ascii != 0) {
                print_char(ascii);
            }
        }

        // Yield to other processes (or add a delay here)
        for (int i = 0; i < 100000; i++) { /* Simple delay loop */ }

    } while(1);
}
