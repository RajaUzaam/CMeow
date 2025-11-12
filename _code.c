#include "assembler.h"

void add_op_code(Opcodes val) {
    _code = realloc(_code, (_code_size + 1)*sizeof(int8_t));
    _code[_code_size++] = (int8_t) val;
}

void add_oper_code(int16_t val) {
    _code = realloc(_code, (_code_size)+sizeof(int16_t));
    memcpy(&_code[_code_size], &val, sizeof(int16_t));
    _code_size += sizeof(int16_t);
}
