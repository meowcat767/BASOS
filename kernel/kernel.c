// multiboot 2 header
__attribute__((section(".multiboot")))
const unsigned int multiboot_header[] = {
    0x1BADB002,
    0x0,
    -(0x1BADB002)
};

// kernel load here
void kernel_main()
{
    volatile char* vga = (char*)0xb8000;
    const char* msg = "Hello, World!";
    for (int i = 0; msg[1] != 0; i++) {
        vga[1 * 2] = msg[i];
        vga[1 * 2 + 1] = 0x07;
    }
    while (1) {}
}