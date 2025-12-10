#ifndef INF_T
#define INF_T

#include "header.h"
#include "instruction_set.h"

// enum {
//     INT32,
//     INT64,
//     REAL,
//     BOOL,
//     CHAR,
//     FUNC,
//     ARR,
//     STR,
//     OBJ,
//     NONE
// };

#endif

int8_t check_type(char* literal);
void fill_value(char* literal, Value* val, bool dynamic);