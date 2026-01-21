#ifndef OPERATIONSH
#define OPERATIONSH

#include "../header.h"
#include "vm_instance.h"

struct VM vm;

bool adjust_overflow(Value* lhs, Value* rhs, ValueType type, bool (of_func)(Value*, Value*, ValueType));

#endif