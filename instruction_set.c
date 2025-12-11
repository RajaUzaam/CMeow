#include "instruction_set.h"

const char op_str[OPCODES_NUM][STD_OPCODE_LEN] = {
    //Has Operands
    "PUSH",
    "STOREG",
    "LOADG",
    "JMP",
    "CALL",
    "ENTER",

    //Function Specific
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
    "ARGS",
    "CARGS",
    "LOCALS",
    "CLOCALS",
    "NAME",
    "START",
    "END"
};

const char type_op_str[1+TYPE_NUM][STD_OPCODE_LEN] = {
    "sep",
    //Primitives
    "BOOL",
    "CHAR",
    "INT32",
    "INT64",
    "REAL32",
    "REAL64",
    "NONE",

    //Dynamic
    "DYNAMIC",
    "PTR",
    "FUNC",
    "ARR",
    "STR",
    "OBJ"
};

typedef enum {
    OPCODE_MAIN = 1,
    OPCODE_LOADER,
    OPCODE_TYPE
} OpTableType;

// Lookup opcode index in the given table type
int32_t get_opc(int32_t table_type, const char *literal) {
    const char (*search_arr)[STD_OPCODE_LEN] = NULL;
    int32_t arr_size = 0;

    switch (table_type) {
        case OPCODE_MAIN:
            search_arr = op_str;
            arr_size = OPCODES_NUM;
            break;
        case OPCODE_LOADER:
            search_arr = loader_op_str;
            arr_size = LOADER_OPCODES_NUM;
            break;
        case OPCODE_TYPE:
            search_arr = type_op_str;
            arr_size = 1 + TYPE_NUM;
            break;
        default:
            return -1; // invalid table type
    }

    for (int32_t i = 0; i < arr_size; i++) {
        if (strcmp(search_arr[i], literal) == 0) {
            // Preserve your original adjustment for loader table
            if (table_type == OPCODE_LOADER) {
                i += TYPE_NUM + 1;
            }
            return i;
        }
    }

    return -1; // not found
}