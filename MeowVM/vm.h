#ifndef VM_H
#define VM_H
#define _CRT_SECURE_NO_WARNINGS

#include "../header.h"
#include "../instruction_set.h"
#include "type_handler.h"
#include "execute.h"

typedef struct Function {
    uint64_t idx;
    uint64_t arg_num;
    uint64_t local_num;
    ValueType *args;
    ValueType *locals;
    uint64_t code_size;
    uint8_t *code;
} Function;

typedef struct Frame {
    Function *func_ptr;
    uint64_t ip;
    int64_t ret_addr;
} Frame;

typedef struct VM {
    Value *stack;
    int64_t sp;
    int64_t bp;

    Frame *call_stack;
    int64_t fp;

    Function **functions;
    uint64_t func_count;
} VM;

typedef struct Instruction {
    uint8_t opcode;
    uint64_t operand;
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

extern uint8_t operand_size;

typedef enum OFMode {
    OF_ERR,
    OF_WRAP,
    OF_PRMT
} OFMode;

extern bool debugger;
extern bool _static;
extern OFMode of_mode;
extern bool last_of;

#endif

void ConstructBin();

//Virual Machine
void InitializeVM();
int ExecuteVM(bool debug_mode, bool repl_mode);

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
bool adjust_overflow(Value* lhs, Value* rhs, ValueType type, bool (of_func)(Value*, Value*, ValueType));

// Instructions
// bool stop   (uint64_t operand);
// bool push   (uint64_t operand);
// bool out    (uint64_t operand);
// bool store  (uint64_t operand);
// bool load   (uint64_t operand);
// bool add    (uint64_t operand);
// bool sub    (uint64_t operand);
// bool mul    (uint64_t operand);
// bool div_   (uint64_t operand); //div() is a c lib ig
// bool jmp    (uint64_t operand);
// bool call   (uint64_t operand);
// bool ret    (uint64_t operand);
// bool load_a (uint64_t operand);
// bool enter  (uint64_t operand);
// bool load_l (uint64_t operand);
// bool store_l(uint64_t operand);
// bool leave  (uint64_t operand);
// bool e_size (uint64_t operand);