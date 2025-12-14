#include "vm.h"

Instruction fetch_instruction() {
    Instruction new_instruction;

    Frame *frame = &vm.call_stack[vm.fp];
    Function *fn = frame->func_ptr;

    uint8_t opcode = fn->code[frame->ip++];
    uint8_t operand = 0;

    if (HasOperand(opcode)) {
        if (frame->ip + OPERAND_SIZE > fn->code_size) {
            printf("Error: Truncated bytecode operand.\n");
            exit(1);
        }
        operand = fn->code[frame->ip++];
    }
    new_instruction.opcode = opcode;
    new_instruction.operand = (uint64_t) operand;
    return new_instruction;
}
