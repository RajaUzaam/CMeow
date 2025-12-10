#include "vm.h"

bool decode_execute(Instruction instruction) {
    switch (instruction.opcode) {
        case STOP: {return stop();}
        case PUSH: {return push(instruction.operand);}
        case OUT: {return out();}
        case STOREG: {return store(instruction.operand);}
        case LOADG: {return load(instruction.operand);}
        case ADD: {return add();}
        case SUB: {return sub();}
        case MUL: {return mul();}
        case DIV: {return div_();}
        case JMP: {return jmp(instruction.operand);}
        case CALL: {return call(instruction.operand);}
        case RET: {return ret();}
        case ENTER: {return enter(co_consts[instruction.operand].value.int_val);}
        case LOADA: {return load_a(instruction.operand);}
        case LOADL: {return load_l(instruction.operand);}
        case STOREL: {return store_l(instruction.operand);}
        default: {
            printf("Unknown Instruction\n");
            return 0;
        }
    }
}
