#include "vm.h"

Instruction fetch_instruction() {
    Instruction new_instruction;

    uint8_t opcode = code[ip++];
    int16_t operand = 0;

    uint8_t operand_size = oper_size(opcode);
    if (operand_size > 0) {
        memcpy(&operand, &code[ip], operand_size);
        ip += operand_size;
    }

    new_instruction.opcode = opcode;
    new_instruction.operand = operand;
    return new_instruction;
}
