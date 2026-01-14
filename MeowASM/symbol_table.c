#include "assembler.h"

uint64_t search_symbol(char* symbol) {
    for (uint64_t i = 0; i < symbol_table_size; i++) {
        if (!strcmp(symbol_table[i], symbol)) {
            return i;
        }
    }
    return -1;
}
