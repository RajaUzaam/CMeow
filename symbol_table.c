#include "assembler.h"

int16_t search_symbol(char* symbol) {
    for (int32_t i = 0; i < symbol_table_size; i++) {
        if (!strcmp(symbol_table[i], symbol)) {
            return i;
        }
    }
    return -1;
}
