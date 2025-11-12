#define _CRT_SECURE_NO_WARNINGS

#include "vm.h"

int32_t *stack = NULL;
int32_t stack_size = 0;
int32_t sp = -1;
int32_t fp = 0;
int32_t ep = 0; //

int32_t *globals = NULL;
int32_t globals_size = 0;

int32_t *co_consts = NULL; //
int32_t co_consts_size = 0; //

uint8_t *code = NULL; //
int32_t code_size = 0; //
int32_t ip = 0; //

int ExecuteVM() {
    Instruction instruction = fetch_instruction();
    bool exit = decode_execute(instruction);
    while (!exit) {
        instruction = fetch_instruction();
        exit = decode_execute(instruction);
    }
    return 0;
}
