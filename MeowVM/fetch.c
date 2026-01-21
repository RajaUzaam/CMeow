#include "vm.h"
#include "fetch.h"

Instruction fetch_instruction() {
    Instruction new_instruction;
    Frame *frame = &vm.call_stack[vm.fp];
    FuncObj *fn = frame->func_ptr;

    uint8_t opcode = fn->code[frame->ip];
    frame->ip += WORD;
    vm.operand_size = IsControl(opcode) ? WORD*4 : vm.operand_size;
    uint64_t operand = 0;

    if (HasOperand(opcode)) {
        if (frame->ip + vm.operand_size > fn->code_size) {
            printf("Error: Truncated bytecode operand.\n");
            exit(1);
        }
        memcpy(&operand, &fn->code[frame->ip], vm.operand_size);
        frame->ip += vm.operand_size;
    }
    vm.operand_size = WORD;
    operand = IsESIZE(opcode) ? (WORD + (opcode - (ESIZE1-1))) : operand;
    new_instruction.opcode = opcode;
    new_instruction.operand = operand;
    return new_instruction;
}
