#ifndef LNKR
#define LNKR

#include "../header.h"
#include "../MeowObjs/objects.h"
#include "../MeowVM/vm.h"

typedef enum RefType {
    JMP_REF,
    FUNC_REF
} RefType;

typedef struct Reference {
    char* name;
    uint64_t func_idx;
    uint64_t addr;
    RefType type;
} Reference;

Value* data;
uint64_t data_size;

Value* constants;
uint64_t constants_size;

Function *functions;
uint64_t func_count;

//Array of actual refrence locations
extern Reference *refrences;
extern uint64_t refrences_size;

//Array of unresolved(address) locations
extern Reference *unresolved_refrences;
extern uint64_t unresolved_refrences_size;

//extern uint8_t *obj_code;

#endif