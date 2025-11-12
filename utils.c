#include "utils.h"

char* trim(char* str) {
    while(*str == ' ' || *str == '\t') str++;
    char* end = str + strlen(str) - 1;
    while(end > str && (*end==' ' || *end=='\t' || *end=='\n')) *end-- = '\0';
    return str;
}

void make_instr(int32_t *len, char **instr, char c) {
    if (c != ' ' && c != '\n') {
        (*instr) = realloc((*instr), (*len)+2);
        (*instr)[(*len)++] = c;
        (*instr)[(*len)] = '\0';
    } else {
        (*len) = 0;
        (*instr)[(*len)] = '\0';
    }
}

void add_to_table(char*** table, int32_t *table_size, char* str) {
    (*table_size)++;
    (*table) = realloc((*table), (*table_size) * sizeof(char*));
    if (!(*table)) {
        perror("realloc failed");
        exit(1);
    }

    int32_t symbol_len = strlen(str);
    (*table)[(*table_size) - 1] = malloc(symbol_len + 1);
    if (!(*table)[(*table_size) - 1]) {
        perror("malloc failed");
        exit(1);
    }
    strcpy((*table)[(*table_size) - 1], str);
}

LoaderOpcodes get_op(char* op) {
    if (!(strcmp(op, "CONST"))) {return CONST;} 
    else if (!(strcmp(op, "GLOBAL"))) {return GLOBAL;}
    else if (!(strcmp(op, "LOCAL"))) {return LOCAL;}
    else if (!(strcmp(op, "NAME"))) {return NAME;}
    else if (!(strcmp(op, "START"))) {return START;} 
    else if (!(strcmp(op, "END"))) {return END;}
    else if (!(strcmp(op, "ARG"))) {return ARG;}
    else {return -1;}
}

Opcodes get_code_op(char* op) {
    if (!(strcmp(op, "STOP"))) {return STOP;}
    else if (!(strcmp(op, "PUSHI"))) {return PUSHI;}
    else if (!(strcmp(op, "LOADG"))) {return LOADG;}
    else if (!(strcmp(op, "STOREG"))) {return STOREG;}
    else if (!(strcmp(op, "JMP"))) {return JMP;}
    else if (!(strcmp(op, "ADDI"))) {return ADDI;}
    else if (!(strcmp(op, "SUBI"))) {return SUBI;}
    else if (!(strcmp(op, "MULI"))) {return MULI;}
    else if (!(strcmp(op, "DIVI"))) {return DIVI;}
    else if (!(strcmp(op, "STOP"))) {return STOP;}
    else if (!(strcmp(op, "RET"))) {return RET;}
    else if (!(strcmp(op, "CALL"))) {return CALL;}
    else if (!(strcmp(op, "ENTER"))) {return ENTER;}
    else if (!(strcmp(op, "LOADA"))) {return LOADA;}
    else if (!(strcmp(op, "LOADL"))) {return LOADL;}
    else if (!(strcmp(op, "STOREL"))) {return STOREL;}
    else if (!(strcmp(op, "OUT"))) {return OUT;} 
    else {return -1;}
}
