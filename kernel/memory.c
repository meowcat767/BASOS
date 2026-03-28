#include "memory.h"
// Simple bump allocator
static uint32_t heap_base = 0;
static uint32_t heap_top = 0;
static uint32_t heap_end = 0;