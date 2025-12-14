#ifndef VM_H
#define VM_H
#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
#include "instruction_set.h"
#include "utils.h"
#include "infer_type.h"
//#include "operations.h"

typedef struct Frame {
    Function *func_ptr;
    int64_t ip;
    int64_t ret_addr;
} Frame;

typedef struct VM {
    Value *stack;
    int64_t sp;
    int64_t bp;

    Frame *call_stack;
    int64_t fp;

    Function *functions;
    uint64_t func_count;
} VM;

typedef struct Instruction {
    uint8_t opcode;
    int64_t operand;
} Instruction;

extern VM vm;

//Storage of Global Variables
extern Value *globals;
extern uint64_t globals_size;

//Code Array that stores the binary instructions
extern uint8_t *code;

//Const table used to refer to constants
extern Value *co_consts;
extern uint64_t co_consts_size;

#endif

void ConstructBin();

//Virual Machine
int ExecuteVM();

//Stack Funcs
void push_val(Value val);
Value pop_val();

//Global Vars Funcs
void store_globals(uint64_t addr, Value val);
Value get_globals(uint64_t addr);

//F-E Cycle Funcs
Instruction fetch_instruction();
bool decode_execute(Instruction Instruction);

//Operations
void perform_operation(Value *total, BinaryOps oper);

// Instructions
bool stop();
bool push(uint64_t addr);
bool out();
bool store(uint64_t addr);
bool load(uint64_t addr);
bool add();
bool sub();
bool mul();
bool div_(); //div() is a c lib ig
bool jmp(int64_t addr);
bool call(uint64_t addr);
bool ret();
bool load_a(uint64_t addr);
bool enter(uint64_t val);
bool load_l(uint64_t addr);
bool store_l(uint64_t addr);
