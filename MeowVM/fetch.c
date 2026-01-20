#include "vm.h"

Instruction fetch_instruction() {
    Instruction new_instruction;
    Frame *frame = &vm.call_stack[vm.fp];
    Function *fn = frame->func_ptr;

    uint8_t opcode = fn->code[frame->ip];
    frame->ip += WORD;
    operand_size = IsControl(opcode) ? WORD*4 : operand_size;
    uint64_t operand = 0;

    if (HasOperand(opcode)) {
        if (frame->ip + operand_size > fn->code_size) {
            printf("Error: Truncated bytecode operand.\n");
            exit(1);
        }
        memcpy(&operand, &fn->code[frame->ip], operand_size);
        frame->ip += operand_size;
    }
    operand_size = WORD;
    operand = IsESIZE(opcode) ? (WORD + (opcode - (ESIZE1-1))) : operand;
    new_instruction.opcode = opcode;
    new_instruction.operand = operand;
    return new_instruction;
}
