#include "shell.h"
#include "keyboard.h"
#include "vga.h"
#include "string.h"

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

void shell_run()
{
    char buffer[128];
    int pos = 0;

    print("\n> ");

    while (1)
    {
        char c = keyboard_getchar();

        if (c == '\n')
        {
            buffer[pos] = 0;
            shell_execute(buffer);
            pos = 0;
            print("\n> ");
        }
        else
        {
            buffer[pos++] = c;

            char s[2];
            s[0] = c;
            s[1] = 0;

            print(s);
        }
    }
}