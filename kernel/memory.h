#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <stddef.h>

// init the heap with a base addr. and size
void memory_init(uint32_t heap_start, uint32_t heap_size);

// allocate "size" bytes from the heap
void* kmalloc(size_t size);

// TODO: free memory
void kfree(void* ptr);
#endif