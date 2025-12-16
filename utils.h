#ifndef UTILS
#define UTILS

#include "header.h"
#include "instruction_set.h"

char* trim(char* str);
void make_instr(uint64_t *len, char **instr, char c);
void add_to_table(char*** table, uint64_t *table_size, char* str);

#endif
