#include "vga.h"

volatile uint16_t* vga_buffer = (volatile uint16_t*)0xB8000;
uint16_t cursor_pos = 0;

void vga_clear() {
    for (uint16_t i = 0; i < 80*25; i++)
        vga_buffer[i] = (0x07 << 8) | ' ';
    cursor_pos = 0;
}

void vga_putchar(char c) {
    if (c == '\n') {
        cursor_pos += 80 - (cursor_pos % 80);
    } else if (c == '\b') {
        if (cursor_pos > 0) cursor_pos--;
        vga_buffer[cursor_pos] = (0x07 << 8) | ' ';
    } else {
        vga_buffer[cursor_pos] = (0x07 << 8) | c;
        cursor_pos++;
    }

    if (cursor_pos >= 80*25)
        cursor_pos = 0; // wrap around (simple)
}

void print(const char* str) {
    while (*str) {
        vga_putchar(*str++);
    }
}