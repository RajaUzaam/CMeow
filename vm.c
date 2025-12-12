#define _CRT_SECURE_NO_WARNINGS

#include "vm.h"

VM vm;

Value *globals = NULL;
int32_t globals_size = 0;

Value *co_consts = NULL;
int32_t co_consts_size = 0;
uint8_t *code = NULL;

void InitializeVM() {
    vm.stack = NULL;
    vm.fp = 0;
    vm.sp = -1;
}

int ExecuteVM() {
    ConstructBin();
    InitializeVM();
    Instruction instruction = fetch_instruction();
    bool exit = decode_execute(instruction);
    while (!exit) {
        instruction = fetch_instruction();
        exit = decode_execute(instruction);
    }
    return 0;
}
