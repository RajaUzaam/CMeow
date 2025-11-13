#include "utils.h"

char* trim(char* str) {
    while(*str == ' ' || *str == '\t') str++;
    char* end = str + strlen(str) - 1;
    while(end > str && (*end==' ' || *end=='\t' || *end=='\n')) *end-- = '\0';
    return str;
}

void make_instr(int32_t *len, char **instr, char c) {
    if (c != ' ' && c != '\n') {
        (*instr) = realloc((*instr), (*len)+2);
        (*instr)[(*len)++] = c;
        (*instr)[(*len)] = '\0';
    } else {
        (*len) = 0;
        (*instr)[(*len)] = '\0';
    }
}

void add_to_table(char*** table, int32_t *table_size, char* str) {
    (*table_size)++;
    (*table) = realloc((*table), (*table_size) * sizeof(char*));
    if (!(*table)) {
        perror("realloc failed");
        exit(1);
    }

    int32_t symbol_len = strlen(str);
    (*table)[(*table_size) - 1] = malloc(symbol_len + 1);
    if (!(*table)[(*table_size) - 1]) {
        perror("malloc failed");
        exit(1);
    }
    strcpy((*table)[(*table_size) - 1], str);
}
