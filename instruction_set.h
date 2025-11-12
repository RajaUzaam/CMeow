#ifndef INSTR_SET
#define INSTR_SET

#include "header.h"

typedef enum Opcodes {
    STOP = 0,
    OUT,
    PUSHI,
    STOREG,
    LOADG,
    ADDI,
    SUBI,
    MULI,
    DIVI,
    JMP,
    CALL,
    RET,
    ENTER,
    LOADA,
    LOADL,
    STOREL
} Opcodes;

typedef enum LoaderOpcodes {
    CONST,
    GLOBAL,
    LOCAL,
    ARG,
    NAME,
    START,
    END,
    UNKNOWN
} LoaderOpcodes;

#endif
