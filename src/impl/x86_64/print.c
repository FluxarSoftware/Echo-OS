#include "print.h"
#include <stdbool.h>

const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

struct Char {
    uint8_t character;
    uint8_t color;
};

struct Char* buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

void clear_row(size_t row) {
    struct Char empty = (struct Char) {
        character: ' ',
        color: color,
    };
    for (size_t col = 0; col < NUM_COLS; col++) {
        buffer[col + NUM_COLS * row] = empty;
    }
}

void print_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        clear_row(i);
    }
}

void scroll() {
    for (size_t row = 1; row < NUM_ROWS; row++) {
        for (size_t col = 0; col < NUM_COLS; col++) {
            buffer[col + NUM_COLS * (row - 1)] = buffer[col + NUM_COLS * row];
        }
    }
    clear_row(NUM_ROWS - 1);
}

void print_newline() {
    col = 0;
    if (row < NUM_ROWS - 1) {
        row++;
    } else {
        scroll();
    }
}
void print_char(char character) {
    if (character == '\n') {
        print_newline();
        return;
    }

    if (character == '\b') {
        if (col == 0) {
           if (row > 0) {
               row--;
               col = NUM_COLS - 1;
           }
        } else {
            col--;
        }
        buffer[col + NUM_COLS * row].character = ' ';
        return;
    }

    if (col >= NUM_COLS) {
        print_newline();
    }

    buffer[col + NUM_COLS * row] = (struct Char) {
        character: (uint8_t) character,
        color: color,
    };

    col++;
}

void print_str(char* str) {
    for (size_t i = 0; 1; i++) {
        char character = (uint8_t) str[i];
        if (character == '\0') {
            return;
        }
        print_char(character);
    }
}

void print_int(int num, int base) {
    char str[32]; // Assuming max 32 digits
    int i = 0;
    bool isNegative = false;

    // Handle negative numbers
    if (num < 0) {
        isNegative = true;
        num = -num;
    }

    // Convert to string (reverse order)
    do {
        int remainder = num % base;
        str[i++] = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
        num = num / base;
    } while (num != 0);

    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';

    // Reverse the string
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    
    print_str(str);
}

void print_set_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}
