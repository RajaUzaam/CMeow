#ifndef VM_H
#define VM_H
#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
#include "instruction_set.h"
#include "utils.h"
#include "infer_type.h"

//Enum for Handling Diff DataTypes

#define PRIMITIVES CHAR+1
#define IsPrimitive(val) (bool)((val >= 0 && val < PRIMITIVES) ? true : false)

//Basic unit of Primitives for our VM
typedef struct Value {
    ValueType type;
    union {
        int32_t int_val;
        float   fl_val;
        char    chr_val;
        bool    bl_val;
    } value;
} Value;

typedef struct Function {
    int32_t idx;
    int32_t arg_num;
    int32_t local_num;
    ValueType *args;
    ValueType *locals;
    int32_t code_size;
    uint8_t *code;
} Function;

typedef struct Frame {
    Function *func_ptr;
    int32_t ip;
    int32_t ret_addr;
} Frame;

typedef struct VM {
    Value *stack;
    int32_t sp;
    int32_t bp;

    Frame *call_stack;
    int32_t fp;

    Function *functions;
    int32_t func_count;
} VM;

typedef struct Instruction {
    uint8_t opcode;
    int16_t operand;
} Instruction;

extern VM vm;

//Storage of Global Variables
extern Value *globals;
extern int32_t globals_size;

//Code Array that stores the binary instructions
extern uint8_t code[];

//Const table used to refer to constants
extern Value *co_consts;
extern int32_t co_consts_size;

#endif

void ConstructBin();

//Virual Machine
int ExecuteVM();

//Stack Funcs
void push_int(Value val);
Value pop_int();

//Global Vars Funcs
void store_globals(int16_t addr, Value val);
Value get_globals(int16_t addr);

//F-E Cycle Funcs
Instruction fetch_instruction();
bool decode_execute(Instruction Instruction);

//Const Table Funcs
int16_t search_const(int32_t val);

// Instructions
bool stop();
bool push(int16_t val);
bool out();
bool store(int16_t addr);
bool load(int16_t addr);
bool add();
bool sub();
bool mul();
bool div_(); //div() is a c lib ig
bool jmp(int16_t addr);
bool call(int16_t addr);
bool ret();
bool load_a(int16_t addr);
bool enter(int32_t val);
bool load_l(int16_t addr);
bool store_l(int16_t addr);
