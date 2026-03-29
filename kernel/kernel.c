#include "memory.h"
#include "shell.h"
#include "gdt.h"
__attribute__((section(".multiboot"), used))
const unsigned int multiboot_header[] = {
    0x1BADB002,
    0x0,
    -(0x1BADB002)
};

void kernel_main()
{
    gdt_install();

    memory_init(0x100000, 0x100000);

    shell_run();
}