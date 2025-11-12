#include "assembler.h"

char** symbol_intr_set = NULL;
int32_t symbol_intr_set_size = 0;

void load_symbol_table() {
    for (int32_t i = 0; i < symbol_intr_set_size; i++) {
        switch (get_op(symbol_intr_set[i])) {
            case GLOBAL: {
                add_to_table(&symbol_intr_set, &symbol_intr_set_size, symbol_intr_set[++i]);
                break;
            } default: {
                printf("Unknown Instruction in Data Table!");
                break;
            }
        }
    }
}

void make_globals(FILE* bc_file) {
    char c;
    char *instr;
    int32_t i = 0;
    instr = malloc(sizeof(char));
    instr[0] = '\0';
    int32_t instr_len;

    while ((c = getc(bc_file)) && c != EOF && get_op(instr) != END) {
        instr_len = (int32_t) strlen(instr);
        if (c == '\n' || c == ' ') {
            switch (get_op(instr)) {
                case GLOBAL: {
                    add_to_table(&symbol_intr_set, &symbol_intr_set_size, "GLOBAL");
                    break;
                }
                default: {
                    for (int32_t i = 0; i < instr_len; i++) {
                        if ((instr[i] >= 'a' && instr[i] <= 'z') || (instr[i] >= 'A' && instr[i] <= 'Z')) {
                            if (i == instr_len-1) {
                                add_to_table(&symbol_intr_set, &symbol_intr_set_size, instr);
                            }
                        } else {
                            break;
                        }
                    }
                    break;
                }
            }
        }
        make_instr(&i, &instr, c);
    }
    load_symbol_table();
}
