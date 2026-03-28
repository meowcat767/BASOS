// multiboot header
__attribute__((section(".multiboot"), used))
const unsigned int multiboot_header[] = {
    0x1BADB002,
    0x0,
    -(0x1BADB002)
};


void kernel_main() {
    volatile char* vga = (volatile char*)0xB8000;
    const char* msg = "Hello, World!";

    for (int i = 0; msg[i] != 0; i++) {
        vga[i * 2] = msg[i];
        vga[i * 2 + 1] = 0x07;
    }

    while (1) {}
}


