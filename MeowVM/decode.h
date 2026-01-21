#ifndef CYC_DECODE
#define CYC_DECODE

#include "../header.h"
#include "fetch.h"

extern bool (*exe_funcs[])(uint64_t);

bool decode_execute(Instruction instruction);

#endif
