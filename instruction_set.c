#include "instruction_set.h"

const char op_str[OPCODES_NUM][STD_OPCODE_LEN] = {
    //Has Operands
    "PUSH",
    "STOREG",
    "LOADG",
    "JMP",
    "CALL",
    "ENTER",
    "LOADA",
    "LOADL",
    "STOREL",

    //Doesn't have Operands
    "STOP",
    "OUT",
    "ADD",
    "SUB",
    "MUL",
    "DIV",
    "RET"
};


const char loader_op_str[LOADER_OPCODES_NUM][STD_OPCODE_LEN] = {
    "CONST",
    "GLOBAL",
    "LOCAL",
    "ARG",
    "NAME",
    "START",
    "END"
};