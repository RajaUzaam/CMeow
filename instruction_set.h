#ifndef INSTR_SET
#define INSTR_SET

#include "header.h"

#define OPCODES_NUM 16
#define LOADER_OPCODES_NUM 7
#define TAKES_OPERAND_NUM 8
#define STD_OPCODE_LEN 8
#define OPERAND_SIZE 2
#define OPCODE_SIZE 1

#define IsOpcode(val) (bool)(( val >= 0 && val < OPCODES_NUM ) ?  true : false)
#define ISLoaderOp(val) (bool)(( val >= 0  && val < LOADER_OPCODES_NUM ) ? true : false)
#define HasOperand(val) (bool)(( val >= 0 && val <= TAKES_OPERAND_NUM ) ? true : false)

typedef enum Opcodes {
    //Has Operands
    PUSH,
    STOREG,
    LOADG,
    JMP,
    CALL,
    ENTER,
    LOADA,
    LOADL,
    STOREL,

    //Doesnt have Operands
    STOP,
    OUT,
    ADD,
    SUB,
    MUL,
    DIV,
    RET

} Opcodes;

typedef enum BinDumpOpcodes {
    HEADER_TABLE = OPCODES_NUM,
    CONSTANTS_TABLE,
    GLOBALS_TABLE,
    FUNCTIONS_TABLE,
    BYTECODE,
    FUNC,
    FUNC_END,
    ARGS,
    LOCALS,
    CODE_OFFSET,
    CODE_SIZE,
    INDEX
} BinDumpOpcodes;

typedef enum ValueType {
    DYNAMIC,
    INT32,
    INT64,
    REAL,
    BOOL,
    CHAR,
    FUNC_TYPE,
    ARR,
    STR,
    OBJ,
    NONE
 } ValueType;

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
