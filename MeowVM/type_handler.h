#ifndef TH
#define TH

#include "../header.h"
#include "../instruction_set.h"

#endif

ValueType resolve_type(Value* lhs, Value* rhs);
void cast_type(Value *val, ValueType target);
void promote(Value *val, ValueType *target_type);