#include "assembler.h"

char** func_instr_set = NULL;
int32_t func_instr_set_size = 0;

char** local_symbol_table = NULL;
int32_t local_symbol_table_size = 0;

char** arg_symbol_table = NULL;
int32_t arg_symbol_table_size = 0;

int16_t search_table(char* symbol, char*** table, int32_t* table_size) {
    for (int32_t i = 0; i < (*table_size); i++) {
        if (!strcmp((*table)[i], symbol)) {
            return i;
        }
    }
    return -1;
}

void resolve_func_set(bool entry) {
    int32_t j = 0;
    while (get_op(func_instr_set[j]) != START) {
        if (entry) {continue;}
        switch(get_op(func_instr_set[j])) {
            case LOCAL: {
                add_to_table(&local_symbol_table, &local_symbol_table_size, func_instr_set[++j]);
                break;
            }
            case NAME: {
                create_ref(func_instr_set[++j], _curr_addr, FUNC_REF);
                break;
            }
            case ARG: {
                add_to_table(&arg_symbol_table, &arg_symbol_table_size, func_instr_set[++j]);
                break;
            }
            default: {
                break;
            }
        }
        j++;
    }
    if (entry) {_entry_point = _curr_addr;}
    for (int32_t i = (j+1); i < func_instr_set_size; i++) {
        if (!entry) {
            switch (get_code_op(func_instr_set[i])) {
                case LOADL: case STOREL: {
                    add_op_code(get_code_op(func_instr_set[i]));
                    add_oper_code(search_table(func_instr_set[++i], &local_symbol_table, &local_symbol_table_size));
                    _curr_addr += 3;
                    break;
                }
                case LOADA: {
                    add_op_code(get_code_op(func_instr_set[i]));
                    add_oper_code(search_table(func_instr_set[++i], &arg_symbol_table, &arg_symbol_table_size));
                    _curr_addr += 3;
                    break;
                }
                default: {
                    break;
                }
            }
        }
        switch (get_code_op(func_instr_set[i])) {
            case PUSH: case ENTER: {
                add_op_code(get_code_op(func_instr_set[i]));
                add_oper_code(search_const_table(atoi(func_instr_set[++i])));
                _curr_addr += 3;
                break;
            }
            case STOREG: case LOADG: {
                add_op_code(get_code_op(func_instr_set[i]));
                add_oper_code(search_symbol(func_instr_set[++i]));
                _curr_addr += 3;
                break;
            }
            case JMP: {
                add_op_code(JMP);
                create_unresolved_ref(func_instr_set[++i], _curr_addr+1, JMP_REF);
                add_oper_code(0);
                _curr_addr += 3;
                break;
            }
            case CALL: {
                add_op_code(CALL);
                create_unresolved_ref(func_instr_set[++i], _curr_addr+1, FUNC_REF);
                add_oper_code(0);
                _curr_addr += 3;
                break;
            }
            case -1: {
                create_ref(func_instr_set[i], _curr_addr, JMP_REF);
                break;
            }
            default: {
                add_op_code(get_code_op(func_instr_set[i]));
                _curr_addr += 1;
                break;
            }
        }
    }
}

void make_func(FILE* bc_file, bool entry_point) {
    char c;
    char *instr;
    int32_t i = 0;
    instr = malloc(sizeof(char));
    instr[0] = '\0';

    while ((c = fgetc(bc_file)) && c != EOF && get_op(instr) != END) {
        if ((c == ' ' || c == '\n') && instr != NULL && strcmp("\0", instr)) {
            add_to_table(&func_instr_set, &func_instr_set_size, instr);
        }
        make_instr(&i, &instr, c);
    }
    resolve_func_set(entry_point);
    func_instr_set = NULL;
    local_symbol_table = NULL;
    arg_symbol_table = NULL;
    func_instr_set_size = 0;
    local_symbol_table_size = 0;
    arg_symbol_table_size = 0;
}
