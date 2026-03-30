#include <stdint.h>
#include "vga.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_COLOR 0x07

volatile uint16_t* vga_buffer = (volatile uint16_t*)0xB8000;
uint16_t cursor_pos = 0;

// low-level port write
static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

// update hardware cursor
static void update_cursor() {
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(cursor_pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((cursor_pos >> 8) & 0xFF));
}

// scroll the screen up by one line
static void scroll() {
    for (int y = 1; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[(y-1)*VGA_WIDTH + x] = vga_buffer[y*VGA_WIDTH + x];
        }
    }
    // clear last line
    for (int x = 0; x < VGA_WIDTH; x++) {
        vga_buffer[(VGA_HEIGHT-1)*VGA_WIDTH + x] = (VGA_COLOR << 8) | ' ';
    }
    cursor_pos -= VGA_WIDTH;
}

void vga_clear() {
    for (int i = 0; i < VGA_WIDTH*VGA_HEIGHT; i++)
        vga_buffer[i] = (VGA_COLOR << 8) | ' ';
    cursor_pos = 0;
    update_cursor();
}

void vga_putchar(char c) {
    if (c == '\n') {
        cursor_pos += VGA_WIDTH - (cursor_pos % VGA_WIDTH);
    } else if (c == '\b') {
        if (cursor_pos > 0) {
            cursor_pos--;
            vga_buffer[cursor_pos] = (VGA_COLOR << 8) | ' ';
        }
    } else {
        vga_buffer[cursor_pos] = (VGA_COLOR << 8) | c;
        cursor_pos++;
    }

    // scroll if needed
    if (cursor_pos >= VGA_WIDTH*VGA_HEIGHT)
        scroll();

    update_cursor();
}

void print(const char* str) {
    while (*str)
        vga_putchar(*str++);
}