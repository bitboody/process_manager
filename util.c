#include "util.h"
#include <stdio.h>
#include <string.h>

void read_input(char *buffer, size_t size)
{
    if (fgets(buffer, size, stdin))
    {
        buffer[strcspn(buffer, "\n")] = 0;
    }
}
