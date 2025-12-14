#include "assembler.h"

uint64_t search_const_table(Value val) {
    for (uint64_t i = 0; i < _co_consts_size; i++) {
        if (val.type == INT32 && _co_consts[i].value.i32 == val.value.i32) { return i; }
        else if (val.type == INT64 && _co_consts[i].value.i64 == val.value.i64) { return i; }
        else if (val.type == CHAR && _co_consts[i].value.chr == val.value.chr) { return i; }
        else if (val.type == BOOL && _co_consts[i].value.bl == val.value.bl) { return i; }
        else if (val.type == REAL32 && _co_consts[i].value.r32 == val.value.r32) { return i; }
        else if (val.type == REAL64 && _co_consts[i].value.r64 == val.value.r64) { return i; }
        else {
            printf("Type not supported yet!\n"); exit(1);
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
