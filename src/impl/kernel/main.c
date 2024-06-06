#include "print.h"

void kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
    print_str("Welcome to Echo-OS!\n");
    // print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    // print_str("\nType something: ");

    // char ch = 0;
    // do {
    //     ch = get_input_keycode();
    //     if (ch) {
    //         uint8_t keycode = get_ascii_char(ch);
    //         switch (keycode) {
    //             case KEY_BACKSPACE:
    //                 handle_backspace();
    //                 break;
    //             case KEY_ENTER:
    //                 handle_enter();
    //                 break;
    //             case KEY_TAB:
    //                 handle_tab();
    //                 break;
    //             case KEY_DELETE:
    //                 handle_delete();
    //                 break;
    //             default:
    //                 if (keycode) {
    //                     print_char(keycode); // Print regular characters
    //                 }
    //                 break;
    //         }
    //     }

    //     // Yield to other processes (or add a delay here)
    //     for (int i = 0; i < 100000; i++) { /* Simple delay loop */ }

    // } while(1);
}
