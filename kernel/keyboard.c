#include "keyboard.h"
#include "io.h"

#define KEYBOARD_DATA_PORT 0x60

static const char scancode_table[] = {
    0, 27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t',
    'q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,
    'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,
    '\\',
    'z','x','c','v','b','n','m',',','.','/',
    0,
    '*',
    0,
    ' '
    };

char keyboard_getchar()
{
    while (!(inb(0x64) & 1));
    uint8_t scancode = inb(KEYBOARD_DATA_PORT);

    if (scancode > 57)
        return 0;

    return scancode_table[scancode];
}