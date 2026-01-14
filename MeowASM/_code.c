#include "assembler.h"

void add_op_code(AFunction* func, Opcodes val) {
    (*func).code = realloc((*func).code, ((*func).code_size + 1)*sizeof(uint8_t));
    (*func).code[(*func).code_size++] = (uint8_t) val;
}

void add_oper_code(AFunction* func, uint64_t val, uint64_t ext_bytes) {
    (*func).code = realloc((*func).code, ((*func).code_size)+((OPERAND_SIZE+ext_bytes)));
    memcpy(&(*func).code[(*func).code_size], &val, (OPERAND_SIZE+ext_bytes));
    (*func).code_size += (OPERAND_SIZE+ext_bytes);
}
