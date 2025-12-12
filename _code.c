#include "assembler.h"

void add_op_code(Function* func, Opcodes val) {
    (*func).code = realloc((*func).code, ((*func).code_size + 1)*sizeof(uint8_t));
    (*func).code[(*func).code_size++] = (uint8_t) val;
}

void add_oper_code(Function* func, int8_t val) {
    (*func).code = realloc((*func).code, ((*func).code_size)+OPERAND_SIZE);
    memcpy(&(*func).code[(*func).code_size], &val, OPERAND_SIZE);
    (*func).code_size += OPERAND_SIZE;
}
