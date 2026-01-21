#ifndef ERR_OBJ
#define ERR_OBJ

#include "../header.h"

typedef enum ERR_CODE {
    STACK_OVERFLOW,
    STACK_UNDERFLOW,
    ZERO_DIVISION,
    CUSTOM,
} ERR_CODE;

typedef struct ErrObj {
    ERR_CODE code;
    uint64_t ip;
    uint64_t line;
    char* msg;
} ErrObj;

#endif