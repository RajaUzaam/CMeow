#include "assembler.h"

uint8_t *bin_code = NULL;
int64_t bin_code_size = 0;

//Array of actual refrence locations
Reference *refrences = NULL;
int32_t refrences_size = 0;

//Array of unresolved(address) locations
Reference *unresolved_refrences = NULL;
int32_t unresolved_refrences_size = 0;

//Symbol Table
char **symbol_table = NULL;
int32_t symbol_table_size = 0;

ValueType *_globals = NULL;
int32_t _globals_size = 0;

Function *_functions = NULL;
int32_t _func_size = 0;

//Final ByteCode
//uint8_t *bytecode = NULL;

//Constants Table
Value *_co_consts = NULL;
int32_t _co_consts_size = 0;

//Entry point variable
int32_t _entry_point = 0;

void ExecuteAssembler(FILE* bc_file) {
    char *instr;
    char c;
    int32_t i = 0;
    instr = malloc(sizeof(char));
    instr[0] = '\0';

    //First Pass
    while ((c = fgetc(bc_file)) != EOF) {
        make_instr(&i, &instr, c);

        //Load Constants
        if (!strcmp(instr, "_consts")) {
            //printf("Loading Constants\n");
            make_consts(bc_file);
        }

        //Load Data
        else if (!strcmp(instr, "_data")) {
            //printf("Loading Data\n");
            make_globals(bc_file);
        }


        //Entry Function 
        //{Only diff is that it notes address in _entry_point and doesn't 
        //make use of function specific Instructions e.g. LOADA}
        else if (!strcmp(instr, "_start")) {
            //rintf("Loading Start\n");
            make_func(bc_file, true);
        }

        //Load Functions
        else if (!strcmp(instr, "_func")) {
            //printf("Loading Func\n");
            make_func(bc_file, false);
        }
    }

    //Second Pass {For now, it only resolves forwards and backward refrences}
    resolve_refs();
    
    dump_bin();

    //These commented lines have helped me immensly when it comes to debugging the assembler
    //Maybe uncommented when debugging is needed

    // printf("#========Final Results==========#:-\n");
    // printf("Symbol Table:-\n");
    // for (int32_t i = 0; i < symbol_table_size; i++) {
    //     printf("[%d] %s\n", i, symbol_table[i]);
    // }
    // printf("Const Table:-\n");
    // for (int32_t i = 0; i < _co_consts_size; i++) {
    //     printf("[%d] %d\n", i, _co_consts[i]);
    // }
    // printf("Instruction set:- \n");
    // for (int32_t i = 0; i < _code_size; i++) {
    //     printf("[%d] 0x%02X\n", i, _code[i]);
    // }

    return;
}
