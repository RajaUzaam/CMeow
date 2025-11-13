#include "assembler.h"

char **symbol_table = NULL;
int32_t symbol_table_size = 0;

Reference *refrences = NULL;
int32_t refrences_size = 0;

Reference *unresolved_refrences = NULL;
int32_t unresolved_refrences_size = 0;

uint8_t *_code = NULL; //
int32_t _code_size = 0; //
int32_t _curr_addr = 0;

int32_t *_co_consts = NULL; //
int32_t _co_consts_size = 0; //

int32_t _entry_point = 0; //

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
        if (!strcmp(instr, "_consts")) {make_consts(bc_file);}

        //Load Data
        else if (!strcmp(instr, "_data")) {make_globals(bc_file);}

        //Entry Function 
        //{Only diff is that it notes address in _entry_point and doesn't 
        //make use of function specific Instructions e.g. LOADA}
        else if (!strcmp(instr, "_start")) {make_func(bc_file, true);}

        //Load Functions
        else if (!strcmp(instr, "_func")) {make_func(bc_file, false);}
    }

    //Second Pass {For now, it only resolves forwards and backward refrences}
    resolve_refs();

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
