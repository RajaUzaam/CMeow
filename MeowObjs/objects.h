#ifndef OBJS
#define OBJS

#include "../header.h"
#include "StrObj.h"
#include "ErrObj.h"

typedef enum ObjType {
    STR,
    ARR,
    LIST,
    OBJ_ERR,
    OBJ_FUNC,
    CTM
} ObjType;

typedef struct FuncObj {
    uint64_t idx;
    uint64_t arg_num;
    uint64_t local_num;
    ValueType *args;
    ValueType *locals;
    uint64_t code_size;
    uint8_t *code;
} FuncObj;

typedef struct Object {
    ObjType type;
    union {
        StrObj str_obj;
        ErrObj err_obj;
        FuncObj* func_obj;
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

typedef struct ValueFlags {
    bool _static;
    bool constant;
    bool param;
} ValueFlags;

typedef struct Value {
    ValueFlags flags;
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