#include "assembler.h"

int16_t search_const_table(Value val) {
    for (int32_t i = 0; i < _co_consts_size; i++) {
        if (val.type == INT32 && _co_consts[i].value.int_val == val.value.int_val) {
            return i;
        }
    }
    return -1;
}

void add_const(Value val) {
    if (search_const_table(val) == -1) {
        _co_consts = realloc(_co_consts, ++_co_consts_size * sizeof(Value));
        _co_consts[_co_consts_size-1] = val;
    }
}
