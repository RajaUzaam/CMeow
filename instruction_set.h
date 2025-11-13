#ifndef INSTR_SET
#define INSTR_SET

#include "header.h"

#define OPCODES_NUM 16
#define LOADER_OPCODES_NUM 7
#define TAKES_OPERAND_NUM 9
#define STD_OPCODE_LEN 8

#define IsOpcode(val) (bool)(( val >= 0 && val < OPCODES_NUM ) ?  true : false)
#define ISLoaderOp(val) (bool)(( val >= 0  && val < LOADER_OPCODES_NUM ) ? true : false)
#define HasOperand(val) (bool)(( val >= 0 && val <= TAKES_OPERAND_NUM ) ? true : false)

typedef enum Opcodes {
    //Has Operands
    PUSHI,
    STOREG,
    LOADG,
    STOP,
    JMP,
    CALL,
    ENTER,
    LOADA,
    LOADL,
    STOREL,

    //Doesnt have Operands
    OUT,
    ADDI,
    SUBI,
    MULI,
    DIVI,
    RET

} Opcodes;

typedef enum LoaderOpcodes {
    CONST,
    GLOBAL,
    LOCAL,
    ARG,
    NAME,
    START,
    END
} LoaderOpcodes;

extern const char op_str[OPCODES_NUM][STD_OPCODE_LEN];
extern const char loader_op_str[LOADER_OPCODES_NUM][STD_OPCODE_LEN];

#endif
