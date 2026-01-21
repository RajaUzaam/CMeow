#ifndef STACKH
#define STACKH

#include "../header.h"
#include "vm_instance.h"

extern struct VM vm;

void push_val(Value val);
Value pop_val();

#endif