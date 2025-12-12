#include "assembler.h"

char** symbol_intr_set = NULL;
int32_t symbol_intr_set_size = 0;

void load_symbol_table() {
    _globals = realloc(_globals, sizeof(_globals)*(symbol_intr_set_size/2));
    for (int32_t i = 0; i < symbol_intr_set_size; i++) {
        int32_t exp_type = get_opc(3, symbol_intr_set[i]);
        if (exp_type == -1) {
            printf("Unknown Instruction in Data Table! %s\n", symbol_intr_set[i]);
            exit(1);
        }
        _globals = realloc(_globals, sizeof(_globals)*(++_globals_size));
        _globals[_globals_size-1] = exp_type;
        add_to_table(&symbol_table, &symbol_table_size, symbol_intr_set[++i]);
    }
}

void make_globals(FILE* bc_file) {
    char c;
    char *instr;
    int32_t i = 0;
    instr = malloc(sizeof(char));
    instr[0] = '\0';
    int32_t instr_len;

    while ((c = getc(bc_file)) && c != EOF && get_opc(2, instr) != END) {
        instr_len = (int32_t) strlen(instr);
        if ((c == '\n' || c == ' ') && (instr[0] != ' ' && instr[0] != '\0')) {
            add_to_table(&symbol_intr_set, &symbol_intr_set_size, instr);
        }
        make_instr(&i, &instr, c);
    }
    load_symbol_table();
}
