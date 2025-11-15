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
    int32_t addr;
    RefType type;
} Reference;

//Array of actual refrence locations
extern Reference *refrences;
extern int32_t refrences_size;

//Array of unresolved(address) locations
extern Reference *unresolved_refrences;
extern int32_t unresolved_refrences_size;

//Symbol Table
extern char **symbol_table;
extern int32_t symbol_table_size;

//Code Table
extern uint8_t *_code;
extern int32_t _code_size;
extern int32_t _curr_addr;

//Final ByteCode
extern uint8_t *bytecode;

//Constants Table
extern int32_t *_co_consts;
extern int32_t _co_consts_size;

//Entry point variable
extern int32_t _entry_point;


#endif

//Assembler Executioner
void ExecuteAssembler(FILE* bc_file);

//Sections
void make_consts(FILE* bc_file);
void make_globals(FILE* bc_file);
void make_func(FILE* bc_file, bool entry_point);

//Symbol Table
int16_t search_symbol(char* symbol);

//Code Table
void add_op_code(Opcodes val);
void add_oper_code(int16_t val);

//Const Table
int16_t search_const_table(int32_t val);
void add_const(int32_t val);

//Reference Control
void create_unresolved_ref(char *name, int32_t addr, RefType type);
void create_ref(char *name, int32_t addr, RefType type);
void resolve_refs();
