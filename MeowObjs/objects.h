#ifndef OBJS
#define OBJS

#include "../header.h"
#include "StrObj.h"

typedef enum ObjType {
    STR,
    ARR,
    LIST,
    CTM
} ObjType;

typedef struct Object {
    ObjType type;
    union {
        StrObj str_obj;
    };
} Object;

#endif