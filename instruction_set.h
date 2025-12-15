#ifndef INSTR_SET
#define INSTR_SET

#include "header.h"

#define OPCODES_NUM RET+1
#define LOADER_OPCODES_NUM END-ARGS+1
#define TAKES_OPERAND_NUM STOREL+1
#define STD_OPCODE_LEN 12
#define OPERAND_SIZE 1//Bytes
#define OPCODE_SIZE 1//Byte
#define WORD 1
#define TYPE_NUM OBJ

#define IsOpcode(val) (bool)(( val >= 0 && val < OPCODES_NUM ) ?  true : false)
#define IsLoaderOp(val) (bool)(( val >= 0  && val < LOADER_OPCODES_NUM ) ? true : false)
#define HasOperand(val) (bool)(( val >= 0 && val < TAKES_OPERAND_NUM ? true : false))

#define PRIMITIVES NONE
#define MAX_TYPE_SUF 5
#define IsPrimitive(val) (bool)((val >= 0 && val < PRIMITIVES) ? true : false)

#define GET_BIT(x, n) (((x) >> (n)) & 1u)
#define IsESIZE(val) (bool)((val >= ESIZE1 && val <= ESIZE7) ? true : false)

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

    //For variable length encoding
    ESIZE1,
    ESIZE2,
    ESIZE3,
    ESIZE4,
    ESIZE5,
    ESIZE6,
    ESIZE7,

    OUT,
    ADD,
    SUB,
    MUL,
    DIV,
    LEAVE,
    RET
} Opcodes;

typedef enum BinDumpOpcodes {
    HEADER_TABLE = OPCODES_NUM,
    CONSTANTS_TABLE,
    GLOBALS_TABLE,
    FUNCTIONS_TABLE,
    BYTECODE,
    CODE_OFFSET,
    CODE_SIZE,
    INDEX
} BinDumpOpcodes;

#define IsInt(val) (int8_t)((val == CHAR || val == INT32 || val == INT64 || val == BOOL) ? val : 0)
#define IsReal(val) (int8_t)((val == REAL32 || val == REAL64) ? val-5 : 0)
#define TypeInt(val) (bool)((val >= BOOL && val <= INT64) ? true : false)
#define TypeReal(val) (bool)((val >= REAL32 && val <= REAL64) ? true: false)
#define IsInt32(val)    (bool)(val == INT32 ? true : false)
#define IsInt64(val)    (bool)(val == INT64 ? true : false)
#define IsBool(val)     (bool)(val == BOOL ? true : false)
#define IsChar(val)     (bool)(val == CHAR ? true : false)
#define IsR32(val)      (bool)(val == REAL32 ? true : false)
#define IsR64(val)      (bool)(val == REAL64 ? true : false)
#define GetBytes(val) (val == BOOL ? 1 : (val == CHAR ? 1 : (val == INT32 ? 4 : (val == INT64 ? 8 : (val == REAL32 ? 4 : (val == REAL64 ? 8 : -1))))))

typedef enum ValueType {
    //Primitives
    BOOL=1,
    CHAR,

    INT32,
    INT64,

    REAL32,
    REAL64,

    NONE,

    //Dynamic
    PTR,
    FUNC,
    ARR,
    STR,
    OBJ
} ValueType;

typedef enum BinaryOps {
    OPADD,
    OPSUB,
    OPMUL,
    OPDIV
} BinaryOps;

typedef enum LoaderOpcodes {
    ARGS = OBJ+1,
    CARGS,
    LOCALS,
    CLOCALS,
    NAME,
    START,
    END
} LoaderOpcodes;

typedef struct Value {
    bool dynamic;
    ValueType type;
    union {
        uint8_t bl;
        uint8_t chr;

        int32_t i32;
        int64_t i64;

        float   r32;
        double  r64;

        void    *ptr;
    } value;
} Value;

extern const char op_str[OPCODES_NUM][STD_OPCODE_LEN];
extern const char loader_op_str[LOADER_OPCODES_NUM][STD_OPCODE_LEN];
extern const char type_op_str[1+TYPE_NUM][STD_OPCODE_LEN];

#endif

uint8_t get_opc(int8_t type, const char* literal);