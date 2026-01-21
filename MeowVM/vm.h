#ifndef VM_H
#define VM_H
#define _CRT_SECURE_NO_WARNINGS

#include "../header.h"
#include "../instruction_set.h"
#include "vm_instance.h"
#include "fetch.h"
#include "decode.h"
#include "execute.h"

extern VM vm;

//Storage of Global Variables
// extern Value *globals;
// extern uint64_t globals_size;

//Code Array that stores the binary instructions
extern uint8_t *code;

//Const table used to refer to constants
// extern Value *co_consts;
// extern uint64_t co_consts_size;

// extern uint8_t operand_size;

#endif

//void ConstructBin();

//Virual Machine
void InitializeVM();
int ExecuteVM(bool debug_mode, bool repl_mode);

//Stack Funcs
// void push_val(Value val);
// Value pop_val();

//Global Vars Funcs
// void store_globals(uint64_t addr, Value val);
// Value get_globals(uint64_t addr);

//F-E Cycle Funcs
//Instruction fetch_instruction();
//bool decode_execute(Instruction Instruction);

//Operations
//bool adjust_overflow(Value* lhs, Value* rhs, ValueType type, bool (of_func)(Value*, Value*, ValueType));
