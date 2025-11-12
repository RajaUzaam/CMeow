#ifndef BC_L
#define BC_L

#include "header.h"
#include "instruction_set.h"
#include "utils.h"

typedef enum RefType {
    JMP_REF,
    FUNC_REF
} RefType;

typedef struct Reference {
    char* name;
    int32_t addr;
    RefType type;
} Reference;

extern Reference *refrences;
extern int32_t refrences_size;

extern Reference *unresolved_refrences;
extern int32_t unresolved_refrences_size;

extern char **symbol_table;
extern int32_t symbol_table_size;

extern uint8_t *_code; //
extern int32_t _code_size; //
extern int32_t _curr_addr;

extern int32_t *_co_consts; //
extern int32_t _co_consts_size; //

extern int32_t _entry_point; //


#endif

//Assembler Executioner
void ExecuteAssembler(FILE* bc_file);

//Sections
void make_consts(FILE* bc_file);
void make_globals(FILE* bc_file);
void make_func(FILE* bc_file, bool entry_point);

//Symbol Table
int16_t search_symbol(char* symbol);

//_code Table
void add_op_code(Opcodes val);
void add_oper_code(int16_t val);

//Const Table
int16_t search_const_table(int32_t val);
void add_const(int32_t val);

//String Utils
void make_instr(int32_t *len, char** instr, char c);
void add_to_table(char*** table, int32_t *table_size, char* str);
int32_t get_op(char* op);
int32_t get_code_op(char* op);

char* trim(char* str);
void make_instr(int32_t *len, char **instr, char c);
void add_to_table(char*** table, int32_t *table_size, char* str);
int32_t get_op(char* op);
int32_t get_code_op(char* op);

//Reference Control
void create_unresolved_ref(char *name, int32_t addr, RefType type);
void create_ref(char *name, int32_t addr, RefType type);
void resolve_refs();
