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

void val_to_table(ValueType** table, int32_t *table_size, ValueType val) {
    (*table_size)++;
    (*table) = realloc((*table), (*table_size) * sizeof(char*));
    if (!(*table)) {
        perror("realloc failed");
        exit(1);
    }
    (*table)[(*table_size)-1] = val;
}

void resolve_func_set(bool entry) {
    int32_t j = 0;
    int32_t _curr_addr = 0;
    int32_t opc;

    if (!entry) {
    while ((opc = get_opc(2, func_instr_set[j])) != START) {
        if (entry) {break;}
        switch(opc) {
            case LOCALS: {
                while ((opc = get_opc(2, func_instr_set[++j])) != CLOCALS) {
                    opc = get_opc(3, func_instr_set[j]);
                    val_to_table(&_functions[_func_size-1].locals, &_functions[_func_size-1].local_num, (ValueType)opc);
                    add_to_table(&local_symbol_table, &local_symbol_table_size, func_instr_set[++j]);
                }
                break;
            }
            case NAME: {
                create_ref(func_instr_set[++j], _func_size-1, -1, FUNC_REF);
                break;
            }
            case ARGS: {
                while ((opc = get_opc(2, func_instr_set[++j])) != CARGS) {
                    opc = get_opc(3, func_instr_set[j]);
                    val_to_table(&_functions[_func_size-1].args, &_functions[_func_size-1].arg_num, (ValueType)opc);
                    add_to_table(&arg_symbol_table, &arg_symbol_table_size, func_instr_set[++j]);
                }
                break;
            }
            default: {
                break;
            }
        }
        j++;
    }
    } 
    else {
        _entry_point = _func_size-1;
    }

    for (int32_t i = (j+1); i < func_instr_set_size; i++) {
        opc = get_code_op(func_instr_set[i]);
        if (!entry) {
            switch (opc) {
                case LOADL: case STOREL: {
                    add_op_code(&_functions[_func_size-1], opc);
                    add_oper_code(&_functions[_func_size-1], search_table(func_instr_set[++i], &local_symbol_table, &local_symbol_table_size));
                    _curr_addr += 3;
                    goto next;
                    break;
                }
                case LOADA: {
                    add_op_code(&_functions[_func_size-1], opc);
                    add_oper_code(&_functions[_func_size-1], search_table(func_instr_set[++i], &arg_symbol_table, &arg_symbol_table_size));
                    _curr_addr += 3;
                    goto next;
                    break;
                }
                default: {
                    break;
                }
            }
        }
        switch (opc) {
            case PUSH: case ENTER: {
                add_op_code(&_functions[_func_size-1], opc);
                Value val;
                bool test = make_value(func_instr_set[++i], &val, true, DYNAMIC);
                //printf("FROM MAKE VAL: %d", test);
                add_oper_code(&_functions[_func_size-1], search_const_table(val));
                _curr_addr += 3;
                //printf("PUSH A VAL\n");
                break;
            }
            case STOREG: case LOADG: {
                add_op_code(&_functions[_func_size-1], opc);
                add_oper_code(&_functions[_func_size-1], search_symbol(func_instr_set[++i]));
                _curr_addr += 3;
                break;
            }
            case JMP: {
                add_op_code(&_functions[_func_size-1], JMP);
                create_unresolved_ref(func_instr_set[++i], _func_size-1, _curr_addr+1, JMP_REF);
                add_oper_code(&_functions[_func_size-1], -1);
                _curr_addr += 3;
                break;
            }
            case CALL: {
                add_op_code(&_functions[_func_size-1], CALL);
                create_unresolved_ref(func_instr_set[++i], _func_size-1, _curr_addr+1, FUNC_REF);
                add_oper_code(&_functions[_func_size-1], -1);
                _curr_addr += 3;
                break;
            }
            case -1: {
                create_ref(func_instr_set[i], _func_size-1, _curr_addr, JMP_REF);
                break;
            }
            default: {
                add_op_code(&_functions[_func_size-1], opc);
                _curr_addr += 1;
                break;
            }
        }
        next:;
    }
}

void make_func(FILE* bc_file, bool entry_point) {
    char c;
    char *instr;
    int32_t i = 0;
    instr = malloc(sizeof(char));
    instr[0] = '\0';

    _functions = realloc(_functions, sizeof(Function) * (++_func_size));
    _functions[_func_size - 1].arg_num = 0;
    _functions[_func_size - 1].local_num = 0;
    _functions[_func_size - 1].locals = NULL;
    _functions[_func_size - 1].args = NULL;
    _functions[_func_size - 1].code_size = 0;
    _functions[_func_size - 1].code = NULL;
    _functions[_func_size - 1].idx = _func_size-1;


    while ((c = fgetc(bc_file)) && c != EOF && (get_opc(2, instr) != END)) {
        if ((c == ' ' || c == '\n') && instr[0] != '\0' && instr != NULL && instr[0] != ' ') {
            //printf("ADD INSTR: %s\n", instr);
            add_to_table(&func_instr_set, &func_instr_set_size, instr);
        }
        make_instr(&i, &instr, c);
        //printf("INSTR-> %s | %c\n", instr, c);
    }
    resolve_func_set(entry_point);
    func_instr_set = NULL;
    local_symbol_table = NULL;
    arg_symbol_table = NULL;
    func_instr_set_size = 0;
    local_symbol_table_size = 0;
    arg_symbol_table_size = 0;
    // printf("Making Function, success\nFinal Verdict:-\n");
    // Function a_func = _functions[_func_size-1];
    // printf("ArgNum: %d\n", a_func.arg_num);
    // printf("LocalNum: %d\n", a_func.local_num);
    // printf("CodeSize: %d\n", a_func.code_size);
    // printf("Args:-\n");
    // for (int32_t i = 0; i < a_func.arg_num; i++) {
    //     printf("%d -> ", a_func.args[i]);
    // }
    // printf("None\n");
    // printf("Locals:-\n");
    // for (int32_t i = 0; i < a_func.local_num; i++) {
    //     printf("%d -> ", a_func.locals[i]);
    // }
    // printf("None\n");
    // printf("Code:-\n");
    // for (int32_t i = 0; i < a_func.code_size; i++) {
    //     printf("%d -> ", a_func.code[i]);
    // }
    // printf("None\n");
}
