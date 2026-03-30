#include "shell.h"
#include "keyboard.h"
#include "vga.h"
#include "string.h"

static char buffer[128];
static int pos = 0;

void shell_execute(char* cmd)
{
    if (strcmp(cmd, "help") == 0)
    {
        print("\ncommands: help hello clear\n");
    }
    else if (strcmp(cmd, "hello") == 0)
    {
        print("\nHello from NiiroOS!\n");
    }
    else if (strcmp(cmd, "clear") == 0)
    {
        vga_clear();
    }
    else
    {
        print("\nUnknown command\n");
    }
}

void shell_init()
{
    pos = 0;
    buffer[0] = 0;
}

void shell_run()
{
    pos = 0;
    print("\n> ");

    while (1)
    {
        char c = keyboard_getchar();
        if (c == 0) continue;

        if (c == '\n')
        {
            buffer[pos] = 0;
            if (pos > 0)
                shell_execute(buffer);
            pos = 0;
            print("\n> ");
        }
        else if (c == '\b')
        {
            if (pos > 0)
            {
                pos--;
                vga_putchar('\b');
            }
        }
        else
        {
            if (pos < 127)
            {
                buffer[pos++] = c;
                vga_putchar(c);
            }
        }
    }
}