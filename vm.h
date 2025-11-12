#ifndef VM_H
#define VM_H
#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
#include "instruction_set.h"
#include "utils.h"

#define OPERAND_SIZE 2
#define OPCODE_SIZE 1

// typedef enum Opcodes {
//     STOP = 0,
//     OUT,
//     PUSHI,
//     STOREG,
//     LOADG,
//     ADDI,
//     SUBI,
//     MULI,
//     DIVI,
//     JMP,
//     CALL,
//     RET,
//     ENTER,
//     LOADA,
//     LOADL,
//     STOREL
// } Opcodes;

typedef struct Instruction {
    uint8_t opcode;
    int16_t operand;
} Instruction;

extern int32_t *stack;
extern int32_t stack_size;
extern int32_t sp;
extern int32_t fp;
extern int32_t ep;

extern int32_t *globals;
extern int32_t globals_size;

extern uint8_t *code;
extern int32_t code_size;
extern int32_t ip;

extern int32_t *co_consts;
extern int32_t co_consts_size;

#endif

int ExecuteVM();

void push_int(int32_t val);
int32_t pop_int();
//void add_op_code(int8_t val);
void store_globals(int16_t addr, int32_t val);
int32_t get_globals(int16_t addr);
Instruction fetch_instruction();
int8_t oper_size(Opcodes opcode);
bool decode_execute(Instruction Instruction);
//int32_t get_op(char* op);
//int32_t get_code_op(char* op);
void add_oper_code(int16_t val);
int16_t search_const(int32_t val);
//void add_const(int32_t val);

//BC Loader
//void loadbc(FILE* bc_file);

// Instructions
bool stop();
bool push_i(int16_t val);
bool out();
bool store_i(int16_t addr);
bool load_i(int16_t addr);
bool add_i();
bool sub_i();
bool mul_i();
bool div_i();
bool jmp(int16_t addr);
bool call(int16_t addr);
bool ret();
bool load_a(int16_t addr);
bool enter(int32_t val);
bool load_l(int16_t addr);
bool store_l(int16_t addr);
