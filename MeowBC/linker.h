#ifndef LNKR
#define LNKR

#include "../header.h"
#include "../MeowObjs/objects.h"
#include "../MeowVM/vm.h"

// typedef enum RefType {
//     JMP_REF,
//     FUNC_REF
// } RefType;

// typedef struct Reference {
//     char* name;
//     uint64_t func_idx;
//     uint64_t addr;
//     RefType type;
// } Reference;

extern Value* data;             // An associated Hash Map
extern uint64_t data_size;

extern Value* constants;        //Sorted Array with Binary Search
extern uint64_t constants_size;

extern Function **functions;    // An associated Hash Map
extern uint64_t func_count;

//Array of actual refrence locations
// extern Reference *refrences;    // Only a Hash Map
// extern uint64_t refrences_size;

// //Array of unresolved(address) locations
// extern Reference *unresolved_refrences; // Simple array with value pointing to an element in the Hash Map of "resolved" refrences
// extern uint64_t unresolved_refrences_size;

//extern uint8_t *obj_code;

#endif

void initialize_linker();
void push_constant(Value constant);
void add_constant(Value constant);
uint64_t get_constant(Value constant);
void add_opcode(Opcodes opcode);
void add_instr(Opcodes opcode, uint64_t operand, size_t bytes);
void add_code(uint8_t val);
void initiate_linking();