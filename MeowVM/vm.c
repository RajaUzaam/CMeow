#define _CRT_SECURE_NO_WARNINGS

#include "vm.h"

VM vm;

Value *globals = NULL;
uint64_t globals_size = 0;

Value *co_consts = NULL;
uint64_t co_consts_size = 0;

uint8_t *code = NULL;

uint8_t operand_size = WORD;

void InitializeVM() {
    vm.stack = NULL;
    vm.fp = 0;
    vm.sp = -1;
}

int ExecuteVM() {
    InitializeVM();
    Instruction instruction = fetch_instruction();
    bool exit = decode_execute(instruction);
    while (!exit) {
        instruction = fetch_instruction();
        exit = decode_execute(instruction);
    }
    return 0;
}
