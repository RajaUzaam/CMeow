#ifndef INF_T
#define INF_T

#include "../header.h"
#include "../instruction_set.h"

typedef struct TypeRepresentation {
    int8_t type;
    bool suffixed;
    char* data;
} TypeRepresentation;

#endif

TypeRepresentation check_type(char* literal);
bool make_const(char* literal, Value* val, void (*const_add)(Value));
bool make_value(char* literal, Value* val, bool dynamic, int8_t type);