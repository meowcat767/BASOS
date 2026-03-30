#include "memory.h"
#include "shell.h"
#include "gdt.h"
#include "vga.h"

void kernel_main()
{
    vga_clear();
    print("NiiroOS Kernel Started\n");
    gdt_install();

    memory_init(0x100000, 0x100000);

    shell_init();
    shell_run();
}