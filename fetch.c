#include "vm.h"

Instruction fetch_instruction() {
    Instruction new_instruction;

    Frame *frame = &vm.call_stack[vm.fp];
    Function *fn = frame->func_ptr;

    uint8_t opcode = fn->code[frame->ip++];
    //vm.call_stack[vm.fp].ip++;
    printf("%u\n", opcode);
    printf("%u\n", HasOperand(opcode));
    int16_t operand = 0;

    if (HasOperand(opcode)) {
        if (frame->ip + OPERAND_SIZE > fn->code_size) {
            printf("Error: Truncated bytecode operand.\n");
            exit(1);
        }
        printf("MEMCPY!\n");
        memcpy(&operand, &(vm.call_stack[vm.fp].func_ptr->code[vm.call_stack[vm.fp].ip]), OPERAND_SIZE);
        vm.call_stack[vm.fp].ip += OPERAND_SIZE;
    }

    new_instruction.opcode = opcode;
    new_instruction.operand = operand;
    return new_instruction;
}
