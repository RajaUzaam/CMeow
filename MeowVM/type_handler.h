#ifndef TH
#define TH

#include "../header.h"
#include "../instruction_set.h"

// typedef struct TypeRepresentation {
//     int8_t type;
//     bool suffixed;
//     char* data;
// } TypeRepresentation;

#endif

//TypeRepresentation check_type(char* literal);
//bool make_const(char* literal, Value* val, void (*const_add)(Value));
//bool make_value(char* literal, Value* val, bool dynamic, int8_t type);
//int64_t to_int64(const Value *val);
//double to_double(const Value *val);
void cast_type(Value *val, ValueType target);
void promote(Value *val, ValueType *target_type);