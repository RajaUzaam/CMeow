#include "assembler.h"

int16_t search_const_table(int32_t val) {
    for (int32_t i = 0; i < _co_consts_size; i++) {
        if (_co_consts[i] == val) {
            return i;
        }
    }
    return -1;
}

void add_const(int32_t val) {
    if (search_const_table(val) == -1) {
        _co_consts = realloc(_co_consts, ++_co_consts_size);
        _co_consts[_co_consts_size-1] = val;
    }
}
