#include <stdint.h>

struct GDTEntry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct GDTPtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static struct GDTEntry gdt[3];
static struct GDTPtr gdt_ptr;

void gdt_install()
{
    gdt_ptr.limit = sizeof(gdt) - 1;
    gdt_ptr.base = (uint32_t)&gdt;

    gdt[0] = (struct GDTEntry){0,0,0,0,0,0};

    gdt[1] = (struct GDTEntry){
        0xFFFF,0,0,0x9A,0xCF,0
    };

    gdt[2] = (struct GDTEntry){
        0xFFFF,0,0,0x92,0xCF,0
    };

    asm volatile(
        "lgdt %0\n"
        "mov $0x10, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        "jmp $0x08, $.reload\n"
        ".reload:\n"
        :
        : "m"(gdt_ptr)
        : "ax"
    );
}