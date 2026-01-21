#ifndef VM_INSTANCE
#define VM_INSTANCE

#include "../header.h"

typedef struct Frame {
    FuncObj *func_ptr;
    uint64_t ip;
    int64_t ret_addr;
} Frame;

typedef enum OFMode {
    OF_ERR,
    OF_WRAP,
    OF_PRMT
} OFMode;

typedef struct VMFlags {
    bool debug_mode;
    bool static_mode;
    bool recent_of;
    char* file_name;
    OFMode of_mode;
} VMFlags;

typedef struct VM {
    VMFlags flags;

    Value* globals; // heap-like
    uint64_t globals_size;

    Value* constants;
    uint64_t constants_size;

    uint64_t operand_size;

    Value *stack;
    uint64_t sp;
    uint64_t bp;

    Frame *call_stack;
    uint64_t fp;

    //FuncObj **functions;
    //uint64_t func_count;
} VM;

#endif