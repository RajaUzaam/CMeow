#ifndef INF_T
#define INF_T

#include "header.h"
#include "instruction_set.h"

#endif

int8_t check_type(char* literal);
bool make_value(char* literal, Value* val, bool dynamic, ValueType type);
int64_t to_int64(const Value *val);
double to_double(const Value *val);
void cast_type(Value *val, ValueType target);
void promote(Value *val, ValueType *target_type);