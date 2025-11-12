#include "vm.h"

bool decode_execute(Instruction instruction) {
    switch (instruction.opcode) {
        case STOP: {return stop();}
        case PUSHI: {return push_i(instruction.operand);}
        case OUT: {return out();}
        case STOREG: {return store_i(instruction.operand);}
        case LOADG: {return load_i(instruction.operand);}
        case ADDI: {return add_i();}
        case SUBI: {return sub_i();}
        case MULI: {return mul_i();}
        case DIVI: {return div_i();}
        case JMP: {return jmp(instruction.operand);}
        case CALL: {return call(instruction.operand);}
        case RET: {return ret();}
        case ENTER: {return enter(co_consts[instruction.operand]);}
        case LOADA: {return load_a(instruction.operand);}
        case LOADL: {return load_l(instruction.operand);}
        case STOREL: {return store_l(instruction.operand);}
        default: {
            printf("Unknown Instruction\n");
            return 0;
        }
    }
}
