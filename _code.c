#include "assembler.h"

void add_op_code(Function* func, Opcodes val) {
    (*func).code = realloc((*func).code, ((*func).code_size + 1)*sizeof(uint8_t));
    (*func).code[(*func).code_size++] = (uint8_t) val;
}

void add_oper_code(Function* func, int16_t val) {
    (*func).code = realloc((*func).code, ((*func).code_size)+sizeof(int16_t));
    memcpy(&(*func).code[(*func).code_size], &val, sizeof(int16_t));
    (*func).code_size += sizeof(int16_t);
}
