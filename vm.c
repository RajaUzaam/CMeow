#define _CRT_SECURE_NO_WARNINGS

#include "vm.h"

VM vm;

Value *globals = NULL;
int32_t globals_size = 0;

Value *co_consts = NULL; //
int32_t co_consts_size = 0; //

uint8_t code[] = {
    // ===============================
    //        HEADER TABLE
    // ===============================
    0x24, 0x00, 0x00, 0x00,      // header size = 36 bytes

    // ---- CONSTANTS TABLE HEADER ----
    CONSTANTS_TABLE,
    0x28, 0x00, 0x00, 0x00,      // offset = 40 (constants data starts here)
    0x00, 0x00, 0x00, 0x00,      // reserved

    // ---- GLOBALS TABLE HEADER ----
    GLOBALS_TABLE,
    0x36, 0x00, 0x00, 0x00,      // offset = 54 (globals data starts here)
    0x00, 0x00, 0x00, 0x00,      // reserved

    // ---- FUNCTIONS TABLE HEADER ----
    FUNCTIONS_TABLE,
    0x3A, 0x00, 0x00, 0x00,      // offset = 58 (functions data starts here)
    0x00, 0x00, 0x00, 0x00,      // reserved

    // ---- BYTECODE SECTION HEADER ----
    BYTECODE,
    0x73, 0x00, 0x00, 0x00,      // offset = 115 (bytecode starts here)
    0x00, 0x00, 0x00, 0x00,      // reserved

    // ===============================
    //       CONSTANTS TABLE
    // ===============================
    0x02, 0x00, 0x00, 0x00,      // table size = 2
    INT32, 0x0A, 0x00, 0x00, 0x00,   // constant 10
    INT32, 0x01, 0x00, 0x00, 0x00,   // constant 1

    // ===============================
    //       GLOBALS TABLE
    // ===============================
    0x00, 0x00, 0x00, 0x00,      // no globals

    // ===============================
    //       FUNCTIONS TABLE
    // ===============================
    0x02, 0x00, 0x00, 0x00,      // number of functions = 2

    // ------- Function 0 -------
    //FUNC,
    INDEX, 0x00,0x00,0x00,0x00,
    CODE_OFFSET, 0x71,0x00,0x00,0x00,0x00,0x00,0x00,0x00,  // func0 code offset = 115
    CODE_SIZE,   0x15,0x00,0x00,0x00,                        // code size = 11 bytes
    ARGS,
    0x01,0x00,0x00,0x00,                                     // arg count
    INT32,
    LOCALS,
    0x01,0x00,0x00,0x00,                                     // local count
    INT32,

    // ------- Function 1 (Entry) -------
    //FUNC,
    0xFF,                                                     // entry point marker
    INDEX, 0x01,0x00,0x00,0x00,
    CODE_OFFSET, 0x86,0x00,0x00,0x00,0x00,0x00,0x00,0x00,    // func1 code offset = 126
    CODE_SIZE,   0x08,0x00,0x00,0x00, 
    //ARGS, 0x00, 0x00, 0x00, 0x00,
    //LOCALS, 0x00, 0x00, 0x00, 0x00,                       // code size = 7 bytes

    // ===============================
    //          BYTECODE
    // ===============================
    // ---- Function 0 bytecode (11 bytes) ----
    //START,
    ENTER, 0x01, 0x00,
    LOADA, 0x00, 0x00,
    STOREL, 0x00, 0x00,
    LOADL, 0x00, 0x00,
    LOADL, 0x00, 0x00,
    LOADL, 0x00, 0x00,
    MUL,
    MUL,
    RET,

    // ---- Function 1 bytecode (7 bytes) ----
    //START,
    PUSH, 0x00, 0x00,
    CALL, 0x00, 0x00,
    OUT,
    STOP
};

void InitializeVM() {
    vm.stack = NULL;
    vm.fp = 0;
    vm.sp = 0;
}

int ExecuteVM() {
    ConstructBin();
    InitializeVM();
    printf("CONSTRUCTED AND INITIALIZED!\n");
    for (int32_t i = 0; i < co_consts_size; i++) {
        printf("-> %d | %d\n", co_consts[i].type, co_consts[i].value.int_val);
    }
    for (int32_t i = 0; i < globals_size; i++) {
        printf("--> %d\n", globals[i].type);
    }
    printf("Func cout; %d | Idx: %d\n", vm.func_count, vm.functions[0].idx);
    for (int32_t i = 0; i < vm.functions[0].code_size; i++) {
        printf("Code: %d\n", vm.functions[0].code[i]);
    }

    printf("======\n=======\n");
    printf("Idx: %d\n",  vm.functions[1].idx);
    for (int32_t i = 0; i < vm.functions[1].code_size; i++) {
        printf("Code: %d\n", vm.functions[1].code[i]);
    }
    printf("\nEntry Point: %d\n", vm.call_stack[0].func_ptr->idx);
    // int32_t j = 0;
    // while (code[j] != STOP) {
    //     print_binary(code[j]);
    // }
    int32_t i = 0;
    Instruction instruction = fetch_instruction();
    printf("Instruction: %d | %d\n", instruction.opcode, instruction.operand);
    bool exit = decode_execute(instruction);
    printf("[%d]\n", ++i);
    while (!exit) {
        instruction = fetch_instruction();
        printf("Instruction: %d | %d\n", instruction.opcode, instruction.operand);
        exit = decode_execute(instruction);
        printf("[%d]\n", ++i);
    }
    return 0;
}
