#ifndef VGA_H
#define VGA_H

#include <stdint.h>

void vga_clear();
void vga_putchar(char c);
void print(const char* str);

#endif