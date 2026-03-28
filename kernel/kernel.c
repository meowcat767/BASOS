#include <stdint.h>

#include "memory.h"

// multiboot header
__attribute__((section(".multiboot"), used))
const unsigned int multiboot_header[] = {
    0x1BADB002,
    0x0,
    -(0x1BADB002)
};






void kernel_main() {
    extern void memory_init(uint32_t heap_start, uint32_t heap_size);

    #define HEAP_START 0x100000  // 1 MB
    #define HEAP_SIZE  0x100000  // 1 MB heap

    memory_init(HEAP_START, HEAP_SIZE);

    // allocate memory
    char* buffer = (char*) kmalloc(128);
    buffer[0] = 'H';
    buffer[1] = 'i';

    volatile char* vga = (volatile char*)0xB8000;
    const char* msg = "Hello, World!";

    for (int i = 0; msg[i] != 0; i++) {
        vga[i * 2] = msg[i];
        vga[i * 2 + 1] = 0x07;
    }

    while (1) {}
}

struct GDTEntry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed));

struct GDTPtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct GDTEntry gdt[3];
struct GDTPtr gdt_ptr;

void gdt_install() {
    gdt_ptr.limit = sizeof(gdt) - 1;
    gdt_ptr.base = (uint32_t)&gdt;

    // Null segment
    gdt[0] = (struct GDTEntry){0,0,0,0,0,0};

    // Code segment
    gdt[1] = (struct GDTEntry){
        .limit_low = 0xFFFF,
        .base_low = 0,
        .base_middle = 0,
        .access = 0x9A,      // executable, readable, ring 0
        .granularity = 0xCF,
        .base_high = 0
    };

    // Data segment
    gdt[2] = (struct GDTEntry){
        .limit_low = 0xFFFF,
        .base_low = 0,
        .base_middle = 0,
        .access = 0x92,      // writable, ring 0
        .granularity = 0xCF,
        .base_high = 0
    };

    asm volatile("lgdt %0" : : "m"(gdt_ptr));
}


