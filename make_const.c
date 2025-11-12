#include "assembler.h"

int32_t *const_set = NULL;
int32_t const_set_size = 0;

void add_const_set(int32_t instr) {
    const_set_size++;
    const_set = realloc(const_set, const_set_size * sizeof(int32_t));
    const_set[const_set_size-1] = instr;
}

void load_co_consts() {
    for (int32_t i = 0; i < const_set_size; i++) {
        switch (const_set[i]) {
            case CONST: {
                add_const(const_set[++i]);
            }
        }
    }
}

void make_consts(FILE* bc_file) {
    char c;
    char *instr;
    int32_t i = 0;
    instr = malloc(sizeof(char));
    instr[0] = '\0';
    int32_t instr_len;

    while ((c = fgetc(bc_file)) != EOF && get_op(instr) != END) {
        instr_len = (int32_t) strlen(instr);
        if ( c == ' ' || c == '\n') {
            switch (get_op(instr)) {
            case CONST:
                add_const_set(CONST); break;
            case END:
                add_const_set(END); break;
            default:
                for (int32_t i = 0; i < instr_len; i++) {
                    if (isdigit(instr[i])) {
                        if (i == (instr_len-1)) {
                            add_const_set(atoi(instr));
                        }
                    } else {break;}
                }
                break;
            }
        }
        make_instr(&i, &instr, c);
    }
    load_co_consts();
    return;
}
