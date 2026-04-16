#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "fstring.h"
void* STRINGS_PAGE = 0x0;
fstring_t fstring(const char* text)
{
    fstring_t new_string; 
    strcpy(new_string.buffer, text);
    new_string.length = strlen(text) + 1;
    return new_string;
}
tempfstring_t tempfstring(size_t size)
{
    tempfstring_t new_temp_string;
    int j = 0;
    uintptr_t current_address = 0x0;
    for (uintptr_t offset = 0; offset < STRINGS_PAGE_SIZE; offset++)
    {
        if (*(uintptr_t*)(STRINGS_PAGE + offset) != 0x0 && *(uintptr_t*)(STRINGS_PAGE + offset) != 0xcc)
        {
            j = 0;
            current_address = 0x0;
            continue;
        } 
        j++;
        if (!current_address)
        {
            current_address = (uintptr_t)(STRINGS_PAGE + offset);
        }
        if (j == size + 1)
        {
            new_temp_string.size = size + 1;
            new_temp_string.buffer = (char*)current_address;
            return new_temp_string;
        }
    }
    return new_temp_string;
}
void freefstring(tempfstring_t string)
{
    if (string.buffer)
    {
        free(string.buffer);
    }
}
bool copytempfstring(tempfstring_t tempstring, const char* buffer)
{
    if (strlen(buffer) + 1 > tempstring.size)
    {
        perror("size too small");
        return false;
    }
    int i = 0;
    for (; buffer[i] != '\0'; i++)
    {
        tempstring.buffer[i] = buffer[i];
    }
    tempstring.buffer[i] = '\0';
    return true;
}
void initfstring()
{
    STRINGS_PAGE = malloc(STRINGS_PAGE_SIZE);
}