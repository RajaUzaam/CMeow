#include "vm.h"

Instruction fetch_instruction() {
    Instruction new_instruction;

    uint8_t opcode = code[ip++];
    int16_t operand = 0;

    bool operand_size = HasOperand(opcode);
    if (operand_size) {
        memcpy(&operand, &code[ip], OPERAND_SIZE);
        ip += OPERAND_SIZE;
    }

    new_instruction.opcode = opcode;
    new_instruction.operand = operand;
    return new_instruction;
}
