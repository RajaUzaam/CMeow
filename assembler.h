#ifndef BC_L
#define BC_L

#include "header.h"
#include "instruction_set.h"
#include "utils.h"
#include "infer_type.h"

//2 Types of Jump and Function Reference
typedef enum RefType {
    JMP_REF,
    FUNC_REF
} RefType;

//Struct for handling a single refrence
typedef struct Reference {
    char* name;
    int32_t func_idx;
    int32_t addr;
    RefType type;
} Reference;

extern uint8_t *bin_code;
extern int64_t bin_code_size;

//Array of actual refrence locations
extern Reference *refrences;
extern int32_t refrences_size;

//Array of unresolved(address) locations
extern Reference *unresolved_refrences;
extern int32_t unresolved_refrences_size;

//Symbol Table
extern char **symbol_table;
extern int32_t symbol_table_size;

extern ValueType *_globals;
extern int32_t _globals_size;

extern Function *_functions;
extern int32_t _func_size;

//Final ByteCode
extern uint8_t *bytecode;

//Constants Table
extern Value *_co_consts;
extern int32_t _co_consts_size;

//Entry point variable
extern int32_t _entry_point;


#endif

//Assembler Executioner
void ExecuteAssembler(FILE* bc_file);

void dump_bin();

//Sections
void make_consts(FILE* bc_file);
void make_globals(FILE* bc_file);
void make_func(FILE* bc_file, bool entry_point);

//Symbol Table
int16_t search_symbol(char* symbol);

//Code Table
void add_op_code(Function* func, Opcodes val);
void add_oper_code(Function* func, int8_t val);

//Const Table
int16_t search_const_table(Value val);
void add_const(Value val);

//Reference Control
void create_unresolved_ref(char *name, int32_t func_addr, int32_t addr, RefType type);
void create_ref(char *name, int32_t func_addr, int32_t addr, RefType type);
void resolve_refs();
