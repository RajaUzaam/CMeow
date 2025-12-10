#ifndef INSTR_SET
#define INSTR_SET

#include "header.h"

#define OPCODES_NUM RET+1
#define LOADER_OPCODES_NUM END+1
#define TAKES_OPERAND_NUM STOREL+1
#define STD_OPCODE_LEN 8
#define OPERAND_SIZE 2//Bytes
#define OPCODE_SIZE 1//Byte

#define IsOpcode(val) (bool)(( val >= 0 && val < OPCODES_NUM ) ?  true : false)
#define IsLoaderOp(val) (bool)(( val >= 0  && val < LOADER_OPCODES_NUM ) ? true : false)
#define HasOperand(val) (bool)(( val >= 0 && val < TAKES_OPERAND_NUM ? true : false))

#define PRIMITIVES CHAR+1
#define IsPrimitive(val) (bool)((val >= 0 && val < PRIMITIVES) ? true : false)

typedef enum Opcodes {
    //Has Operands
    PUSH,
    STOREG,
    LOADG,
    JMP,
    CALL,
    ENTER,

    //Function Specific
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
    ARGS,
    LOCALS,
    CODE_OFFSET,
    CODE_SIZE,
    INDEX
} BinDumpOpcodes;

typedef enum ValueType {
    //Primitives
    BOOL,
    CHAR,
    INT16,
    INT32,
    INT64,
    REAL32,
    REAL64,

    //Dynamic
    DYNAMIC,
    PTR,
    FUNC_TYPE,
    ARR,
    STR,
    OBJ,
    NONE
} ValueType;

typedef enum LoaderOpcodes {
    CONST,//
    GLOBAL,//
    LOCAL,//
    ARG,//
    NAME,
    START,
    END
} LoaderOpcodes;

typedef struct Value {
    bool dynamic;
    ValueType type;
    union {
        int32_t int_val;

        bool    bl;

        char    chr;
        int16_t i16;
        int32_t i32;
        int64_t i64;

        float   r32;
        double  r64;

        void    *ptr;
    } value;
} Value;

typedef struct Function {
    int32_t idx;
    int32_t arg_num;
    int32_t local_num;
    ValueType *args;
    ValueType *locals;
    int32_t code_size;
    uint8_t *code;
} Function;

extern const char op_str[OPCODES_NUM][STD_OPCODE_LEN];
extern const char loader_op_str[LOADER_OPCODES_NUM][STD_OPCODE_LEN];

#endif
