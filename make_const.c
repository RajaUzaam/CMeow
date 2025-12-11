#include "assembler.h"

Value *const_set = NULL;
int32_t const_set_size = 0;

void readWord(FILE* bc_file, char** word) {
    char c;
    int32_t word_size = 0;
    while ((c = fgetc(bc_file)) != ' ' && c != '\n') {
        (*word) = realloc((*word), ++word_size);
        (*word)[word_size-1] = c;
    }
    (*word) = realloc((*word), ++word_size);
    (*word)[word_size-1] = '\0';
    return;
}

void add_const_set(Value const_data) {
    const_set_size++;
    const_set = realloc(const_set, const_set_size * sizeof(Value));
    const_set[const_set_size-1] = const_data;
    //add_const(const_data);
}

void load_co_consts() {
    for (int32_t i = 0; i < const_set_size; i++) {
        add_const(const_set[i]);
    }
}

void make_consts(FILE* bc_file) {
    char c;
    char *instr;
    int32_t i = 0;
    instr = malloc(sizeof(char));
    instr[0] = '\0';
    int32_t instr_len;

    while ((c = fgetc(bc_file)) != EOF && get_opc(2, instr) != END) {
        instr_len = (int32_t) strlen(instr);
        if ( (c == ' ' || c == '\n') && (instr[0] != ' ' && instr_len > 1) ) {
            char* consdata = NULL;
            readWord(bc_file, &consdata);
            Value val;
            int32_t exp_type = get_opc(3, instr);
            if (exp_type >= 0) {
                if (!make_value(consdata, &val, true, (ValueType)exp_type)) {
                    printf("Unknown DataType!\n"); exit(1);
                }
            }
            add_const_set(val);
        }
        make_instr(&instr_len, &instr, c);
    }
    load_co_consts();
    
    return;
}
