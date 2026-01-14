#include "vm.h"

bool (*exe_funcs[])(uint64_t) = {
    push, 
    store, 
    load, 
    jmp, 
    call, 
    enter, 
    load_a, 
    load_l, 
    store_l, 
    stop, 
    e_size, e_size, e_size, e_size, e_size, e_size, e_size, 
    out, 
    add, 
    sub, 
    mul, 
    div_, 
    leave, 
    ret
};

bool decode_execute(Instruction instruction) {
    if (IsOpcode(instruction.opcode)) {
        return exe_funcs[instruction.opcode](instruction.operand);
    } else {
        printf("Unknown Instruction!\n"); exit(1);
    }
}
