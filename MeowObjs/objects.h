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

typedef enum ValueType {
    //Primitives
    BOOL=1,
    CHAR,

    INT32,
    REAL32,

    INT64,
    REAL64,

    PTR,

    NONE,

    //Dynamic
    OBJ
} ValueType;

typedef struct Value {
    bool dynamic;
    bool constant;
    ValueType type;
    union {
        bool bl;
        uint8_t chr;

        int32_t i32;
        int64_t i64;

        float   r32;
        double  r64;

        void    *ptr;

        Object obj;
    };
} Value;

#endif