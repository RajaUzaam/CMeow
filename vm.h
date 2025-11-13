#ifndef VM_H
#define VM_H
#define _CRT_SECURE_NO_WARNINGS

#include "header.h"
#include "instruction_set.h"
#include "utils.h"

#define OPERAND_SIZE 2//bytes
#define OPCODE_SIZE 1//byte

typedef enum ValueType {
    INT,
    REAL,
    BOOL,
    CHAR
} ValueType;

typedef struct PointValue {
    ValueType type;
    union {
        int16_t* int_val;
        float* fl_val;
        char* char_val;
        bool* bool_val;
    } value;
} PointValue;

//This struct will be returned by "Fetch" and loaded by the "Decode"
typedef struct Instruction {
    uint8_t opcode;
    int16_t operand;
} Instruction;

//Stack and related registers
extern int32_t *stack;
extern int32_t stack_size;
extern int32_t sp;
extern int32_t fp;

//Storage of Global Variables
extern int32_t *globals;
extern int32_t globals_size;

//Code Array that stores the binary instructions
extern uint8_t *code;
extern int32_t code_size;
extern int32_t ip;

//Const table used to refer to constants
extern int32_t *co_consts;
extern int32_t co_consts_size;

typedef struct VMInstance {
    int name;
} VMInstance;

#endif

//Virual Machine
int ExecuteVM();

//Stack Funcs
void push_int(int32_t val);
int32_t pop_int();

//Global Vars Funcs
void store_globals(int16_t addr, int32_t val);
int32_t get_globals(int16_t addr);

//F-E Cycle Funcs
Instruction fetch_instruction();
bool decode_execute(Instruction Instruction);

//Const Table Funcs
int16_t search_const(int32_t val);

//Code Funcs
//int8_t oper_size(Opcodes opcode);

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
