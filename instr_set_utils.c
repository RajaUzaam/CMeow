#include "instruction_set.h"
#include "utils.h"

int8_t get_op(char* op) {
    for (int8_t i = 0; i < LOADER_OPCODES_NUM; i++) {
        if (!strcmp(loader_op_str[i], op)) {
            return i;
        }
    } return -1;
}

int8_t get_code_op(char* op) {
    for (int8_t i = 0; i < OPCODES_NUM; i++) {
        if (!strcmp(op_str[i], op)) {
            return i;
        }
    } return -1;
}