#include "assembler.h"

#define HEADER_SIZE 40

int64_t const_table_addr = 0;
int64_t globals_table_addr = 0;
int64_t functions_table_addr = 0;
int64_t bytecode_addr = 0;
int64_t curr_addr = 0;

void makeHeader() {
    bin_code_size += 40;
    const_table_addr = bin_code_size;
    bin_code_size += 4;
    for (int32_t i = 0; i < _co_consts_size; i++) {
        if (_co_consts[i].type == INT32) {
            bin_code_size += 5;
        }
    }
    globals_table_addr = bin_code_size;
    bin_code_size += 4;
    bin_code_size += _globals_size;
    functions_table_addr = bin_code_size;
    bin_code_size += 4;
    for (int32_t i = 0; i < _func_size; i++) {
        if (i == _entry_point) {
            bin_code_size += 20;
        } else {
            bin_code_size += 29;
            bin_code_size += _functions[i].arg_num;
            bin_code_size += _functions[i].local_num;
        }
    }
    bytecode_addr = bin_code_size;
    for (int32_t i = 0; i < _func_size; i++) {
        bin_code_size += _functions[i].code_size;
    }

    bin_code = realloc(bin_code, bin_code_size);
    memcpy(&bin_code[curr_addr], &((uint8_t[]) {0x24, 0x00, 0x00, 0x00}), sizeof(int32_t));
    curr_addr += 4;
    bin_code[curr_addr++] = CONSTANTS_TABLE;
    memcpy(&bin_code[curr_addr], &const_table_addr, sizeof(int64_t));
    curr_addr += sizeof(int64_t);
    bin_code[curr_addr++] = GLOBALS_TABLE;
    memcpy(&bin_code[curr_addr], &globals_table_addr, sizeof(int64_t));
    curr_addr += sizeof(int64_t);
    bin_code[curr_addr++] = FUNCTIONS_TABLE;
    memcpy(&bin_code[curr_addr], &functions_table_addr, sizeof(int64_t));
    curr_addr += sizeof(int64_t);
    bin_code[curr_addr++] = BYTECODE;
    memcpy(&bin_code[curr_addr], &bytecode_addr, sizeof(int64_t));
    curr_addr += sizeof(int64_t);
}

void writeConsts() {
    int32_t curr_const_addr = const_table_addr+4;
    memcpy(&bin_code[const_table_addr], &_co_consts_size, sizeof(int32_t));
    for (int32_t i = 0; i < _co_consts_size; i++) {
        bin_code[curr_const_addr++] = _co_consts[i].type;
        switch (_co_consts[i].type) {
            case INT32: memcpy(&bin_code[curr_const_addr], &_co_consts[i].value.i32, GetBytes(_co_consts[i].type)); break;
            case INT64: memcpy(&bin_code[curr_const_addr], &_co_consts[i].value.i64, GetBytes(_co_consts[i].type)); break;
            case BOOL: memcpy(&bin_code[curr_const_addr], &_co_consts[i].value.bl, GetBytes(_co_consts[i].type)); break;
            case CHAR: memcpy(&bin_code[curr_const_addr], &_co_consts[i].value.chr, GetBytes(_co_consts[i].type)); break;
            case REAL32: memcpy(&bin_code[curr_const_addr], &_co_consts[i].value.r32, GetBytes(_co_consts[i].type)); break;
            case REAL64: memcpy(&bin_code[curr_const_addr], &_co_consts[i].value.r64, GetBytes(_co_consts[i].type)); break;
            default: exit(1);
        }
        //memcpy(&bin_code[curr_const_addr], &_co_consts[i].value.int_val, GetBytes(_co_consts[i].type));
        curr_const_addr += GetBytes(_co_consts[i].type);
    }
}

void writeGlobals() {
    memcpy(&bin_code[globals_table_addr], &_globals_size, sizeof(int32_t));
    for (int32_t i = (globals_table_addr+4); i < (globals_table_addr+4+_globals_size); i++) {
        bin_code[i] = _globals[i-(globals_table_addr+4)];
    }
}

int64_t curr_bytecode_addr = 0;
int64_t curr_func_addr = 0;

void writeByteCode(uint8_t** src_code, int32_t* src_code_size, uint8_t** dest_code, int64_t* dest_code_addr) {
    for (int32_t i = 0; i < *src_code_size; i++) {
        (*dest_code)[(*dest_code_addr)++] = (*src_code)[i];
    }
}

void writeFuncs() {
    curr_func_addr = functions_table_addr;//((int64_t) sizeof(int32_t));
    curr_bytecode_addr = bytecode_addr;
    memcpy(&bin_code[functions_table_addr], &_func_size, sizeof(int32_t));
    curr_func_addr += 4;
    for (int32_t i = 0; i < _func_size; i++) {
        if (i == _entry_point) {
            bin_code[curr_func_addr++] = 0xFF;
            bin_code[curr_func_addr++] = INDEX;
            memcpy(&bin_code[curr_func_addr], &_functions[i].idx, sizeof(int32_t));
            curr_func_addr += sizeof(int32_t);
            bin_code[curr_func_addr++] = CODE_OFFSET;
            memcpy(&bin_code[curr_func_addr], &curr_bytecode_addr, sizeof(int64_t));
            curr_func_addr += sizeof(int64_t);
            bin_code[curr_func_addr++] = CODE_SIZE;
            memcpy(&bin_code[curr_func_addr], &_functions[i].code_size, sizeof(int32_t));
            curr_func_addr += sizeof(int32_t);
            writeByteCode(&_functions[i].code, &_functions[i].code_size, &bin_code, &curr_bytecode_addr);
        } else {
            bin_code[curr_func_addr++] = INDEX;
            memcpy(&bin_code[curr_func_addr], &_functions[i].idx, sizeof(int32_t));
            curr_func_addr += sizeof(int32_t);
            bin_code[curr_func_addr++] = CODE_OFFSET;
            memcpy(&bin_code[curr_func_addr], &curr_bytecode_addr, sizeof(int64_t));
            curr_func_addr += sizeof(int64_t);
            bin_code[curr_func_addr++] = CODE_SIZE;
            memcpy(&bin_code[curr_func_addr], &_functions[i].code_size, sizeof(int32_t));
            curr_func_addr += sizeof(int32_t);

            //ARGS
            bin_code[curr_func_addr++] = ARGS;
            memcpy(&bin_code[curr_func_addr], &_functions[i].arg_num, sizeof(int32_t));
            curr_func_addr += sizeof(int32_t);
            for (int32_t j = 0; j < _functions[i].arg_num; j++) {
                bin_code[curr_func_addr++] = _functions[i].args[j];
            }

            //LOCALS
            bin_code[curr_func_addr++] = LOCALS;
            memcpy(&bin_code[curr_func_addr], &_functions[i].local_num, sizeof(int32_t));
            curr_func_addr += sizeof(int32_t);
            for (int32_t j = 0; j < _functions[i].local_num; j++) {
                bin_code[curr_func_addr++] = _functions[i].locals[j];
            }
            writeByteCode(&_functions[i].code, &_functions[i].code_size, &bin_code, &curr_bytecode_addr);
        }
    }
}

void dump_bin() {
    makeHeader();
    writeConsts();
    writeGlobals();
    writeFuncs();
    // for (int32_t i = 0; i < bin_code_size; i++) {
    //     printf("0x%02X, ", bin_code[i]);
    // }
    // printf("None\n");
}