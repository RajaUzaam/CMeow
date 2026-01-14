#include "file_handler.h"

void Read(char* file_name, char** src, uint64_t* srclen) {
    static char c;

    FILE* file;
    file = fopen(file_name, "r");

    while ((c = fgetc(file)) && c != EOF) {
        *src = realloc(*src, ++(*srclen));
        (*src)[(*srclen)-1] = c;
    }
    *src = realloc(*src, (*srclen) + 1);
    (*src)[(*srclen)] = '\0';

    fclose(file);
    return;
}