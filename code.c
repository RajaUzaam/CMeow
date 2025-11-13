//#include "vm.h"

// int8_t oper_size(Opcodes opcode) {
//     switch (opcode) {
//         case STOP: case OUT: case ADDI: case SUBI: case MULI: case DIVI: case RET: return 0; break;
//         case PUSHI: case STOREG: case LOADG: case JMP: case CALL: case ENTER: case LOADA: case STOREL: case LOADL: return OPERAND_SIZE; break;
//         default: return -1;
//     }
// }