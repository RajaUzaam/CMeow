#include "vm.h"
#include "assembler.h"
#include "instruction_set.h"

int main(int argc, char* argv[]) {
    
    // if (argc < 2) {
    //     perror("\nBytecode Filename not provided!");
    // }

    //Assembler
    //FILE* bc_file = fopen(argv[1], "r");
    //ExecuteAssembler(bc_file);
    //fclose(bc_file);

    //Bin Loader
    //code = _code;
    //code_size = _code_size;
    //co_consts = _co_consts;
    //co_consts_size = _co_consts_size;
    //ip = _entry_point;

    // code = {
    //     HEADER_TABLE,
    //     CONST_TABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //     GLOBALS_TABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //     FUNCTION_TABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //     BYTECODE_TABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    //     //Constants Table
    //     0x0A, 0x00, 0x00, 0x00, //Const Table Size
    //     INT32, 0x0A, 0x00, 0x00, 0x00, 
    //     INT32, 0x01, 0x00, 0x00, 0x00,

    //     //Globals Table
    //     0x00, 0x00, 0x00, 0x00,//Globals Size
        
    //     //Function Table
    //     0x02, 0x00, 0x00, 0x00,//Num of Functions
    //     //New Functions
    //     FUNC,
    //     INDEX, 0x00, 0x00, 0x00, 0x00,
    //     CODE_OFFSET, 0x00, 0x00, 0x00, 0x00,
    //     CODE_SIZE, 0x18, 0x00, 0x00, 0x00
    //     0x01, 0x00, 0x00, 0x00,//Arg Num
    //     ARGS,
    //     INT32,
    //     0x01, 0x00, 0x00, 0x00, //Local Num
    //     LOCALS,
    //     INT32,

    //     //New Entry Point Function
    //     FUNC,
    //     0xFF, // Defines Entry Point Function
    //     INDEX, 0x01, 0x00, 0x00, 0x00,
    //     CODE_OFFSET, 0x18, 0x00, 0x00, 0x00,
    //     CODE_SIZE, 0x09, 0x00, 0x00, 0x00,

    //     //ByteCodes
    //     START, 
    //     ENTER, 0x01, 0x01,
    //     LOADA, 0x00, 0x00,
    //     STOREL, 0x00, 0x00,
    //     LOADL, 0X00, 0x00,
    //     LOADL, 0X00, 0x00,
    //     LOADL, 0X00, 0x00,
    //     MUL,
    //     MUL,
    //     RET,

    //     START,
    //     PUSH, 0x00, 0x00,
    //     CALL, 0x00, 0x00, //Func Idx
    //     OUT,
    //     STOP
    // };

    //Virtual Machine
    ExecuteVM();

    return 0;
}
