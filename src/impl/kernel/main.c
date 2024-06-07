#include <stdint.h>
#include "print.h"
#include "keyboard.h"

void clear_screen() {
    uint16_t *video_memory = (uint16_t *)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i] = 0x0720;
    }
}
void kernel_main() {
  clear_screen();

  print_clear();
  print_set_color(PRINT_COLOR_YELLOW, PRINT_COLOR_BLACK);
  print_str("Welcome to 64-bit kernel!");
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
      for (int i = 0; i < 100000; i++) { /* Simple delay loop */ }

  } while(1);
}
