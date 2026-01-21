#ifndef TH
#define TH

#include "../header.h"
#include "../instruction_set.h"

#endif

void to_bl(Value *val);
void to_i32(Value *val);
void to_i64(Value *val);
void to_r32(Value *val);
void to_r64(Value *val);
void to_chr(Value *val);

ValueType resolve_type(Value* lhs, Value* rhs);
bool add_overflow(Value* lhs, Value* rhs, ValueType type);
bool sub_overflow(Value* lhs, Value* rhs, ValueType type);
bool mul_overflow(Value* lhs, Value* rhs, ValueType type);
bool div_overflow(Value* lhs, Value* rhs, ValueType type);