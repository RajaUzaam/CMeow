#include "vm.h"

int8_t oper_size(Opcodes opcode) {
    switch (opcode) {
        case STOP: case OUT: case ADDI: case SUBI: case MULI: case DIVI: case RET: return 0; break;
        case PUSHI: case STOREG: case LOADG: case JMP: case CALL: case ENTER: case LOADA: case STOREL: case LOADL: return OPERAND_SIZE; break;
        default: return -1;
    }
}
// void add_op_code(int8_t val) {
//     code = realloc(code, (++code_size) * sizeof(int8_t));
//     code[code_size-1] = val;
// }

// void add_oper_code(int16_t val) {
//     int new_size = code_size + sizeof(int16_t);
//     code = realloc(code, new_size);
//     memcpy(&code[code_size], &val, sizeof(int16_t));
//     code_size = new_size;
// }
