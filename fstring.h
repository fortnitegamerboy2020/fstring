#include <stdio.h>
#ifndef STRINGS_PAGE_SIZE
#define STRINGS_PAGE_SIZE 4096
#endif
#ifndef STRING_MAX_LENGTH
#define STRING_MAX_LENGTH 255
#endif
typedef struct {
    char buffer[STRING_MAX_LENGTH];
    size_t length;
} fstring_t;
typedef struct {
    char* buffer;
    size_t size;
} tempfstring_t;


fstring_t fstring(const char* text);
tempfstring_t tempfstring(size_t size);
void freefstring(tempfstring_t string);
bool copytempfstring(tempfstring_t tempstring, const char* buffer);
void initfstring();