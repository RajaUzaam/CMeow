#ifndef CYC_FTCH
#define CYC_FTCH

#include "../header.h"

typedef struct Instruction {
    uint8_t opcode;
    uint64_t operand;
} Instruction;

Instruction fetch_instruction();

#endif