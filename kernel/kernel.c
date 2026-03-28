void kernel_main()
{
    char* vga = (char*)0xb8000;
    const char* msg = "Hello, World!";
    for (int i = 0; msg[1] != 0; i++) {
        vga[1 * 2] = msg[i];
        vga[1 * 2 + 1] = 0x07;
    }
    while (1) {}
}