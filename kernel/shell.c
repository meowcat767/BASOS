#include "shell.h"
#include <stdint.h>

#define VGA_MEMORY ((volatile uint16_t*)0xB8000)

static int cursor = 0;

static void print(const char* str)
{
    while (*str)
    {
        VGA_MEMORY[cursor++] = (*str | 0x0700);
        str++;
    }
}

static int strcmp(const char* a, const char* b)
{
    while (*a && *b)
    {
        if (*a != *b)
            return 1;
        a++;
        b++;
    }

    return *a != *b;
}

void shell_execute(char* cmd)
{
    if (!strcmp(cmd, "help"))
    {
        print("\ncommands: help hello clear\n");
    }
    else if (!strcmp(cmd, "hello"))
    {
        print("\nHello from NiiroOS!\n");
    }
    else if (!strcmp(cmd, "clear"))
    {
        for (int i = 0; i < 80*25; i++)
            VGA_MEMORY[i] = (' ' | 0x0700);
        cursor = 0;
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
        char c = keyboard_getchar();   // TODO: keyboard driver

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