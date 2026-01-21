#ifndef GLBS
#define GLBS

#include "../header.h"
#include "vm_instance.h"

extern struct VM vm;

void store_globals(uint64_t addr, Value val);
Value get_globals(uint64_t addr);

#endif