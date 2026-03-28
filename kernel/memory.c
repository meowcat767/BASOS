#include "memory.h"

// Simple bump allocator
static uint32_t heap_base = 0;
static uint32_t heap_top  = 0;
static uint32_t heap_end  = 0;

void memory_init(uint32_t start, uint32_t size) {
    heap_base = start;
    heap_top  = start;
    heap_end  = start + size;
}

void* kmalloc(size_t size) {
    // Align size to 4 bytes
    size = (size + 3) & ~3;

    if (heap_top + size > heap_end) {
        // Out of memory
        return 0;
    }

    void* ptr = (void*)heap_top;
    heap_top += size;
    return ptr;
}

void kfree(void* ptr) {
    // Not implemented yet
    (void)ptr;
}