#include "vm.h"

static int32_t read_int32(uint8_t *code, int64_t offset) {
    int32_t val;
    memcpy(&val, &code[offset], sizeof(int32_t));
    return val;
}

static int64_t read_int64(uint8_t *code, int64_t offset) {
    int64_t val;
    memcpy(&val, &code[offset], sizeof(int64_t));
    return val;
}

// Construct constants table
void construct_const_table(int64_t addr) {
    co_consts_size = read_int32(code, addr);
    co_consts = realloc(co_consts, sizeof(Value) * co_consts_size);

    int64_t i = addr + 4; // skip table size
    for (int32_t idx = 0; idx < co_consts_size; idx++) {
        co_consts[idx].type = code[i++]; // type byte
        switch (co_consts[idx].type) {
            case INT32:
                co_consts[idx].value.int_val = read_int32(code, i);
                i += sizeof(int32_t);
                break;
            default:
                perror("Unknown Const Type!");
                exit(1);
        }
    }
}

// Construct globals table
void construct_global_table(int64_t addr) {
    globals_size = read_int32(code, addr);
    globals = realloc(globals, sizeof(Value) * globals_size);

    int64_t i = addr + 4; // skip table size
    for (int32_t idx = 0; idx < globals_size; idx++) {
        globals[idx].type = code[i++];
        switch (globals[idx].type) {
            case INT32:
                globals[idx].value.int_val = 0; // initialize
                break;
            default:
                perror("Unknown Global Type!");
                exit(1);
        }
    }
}

// Load function bytecode
void load_func_bytecode(int32_t idx, int64_t addr, uint8_t **bc_code, int32_t size) {
    vm.functions[idx].code_size = size;
    *bc_code = malloc(sizeof(uint8_t) * size);
    memcpy(*bc_code, &code[addr], size);
}

// Construct functions table
void construct_func_table(int64_t addr, int32_t func_count) {
    int64_t ip = addr;

    for (int32_t j = 0; j < func_count; j++) {
        int32_t read_opcodes = 0;
        bool entry = false;
        if (code[ip] == 0xFF) {
            ip++;
            entry = true;
        }
        int32_t idx = -1;
        int64_t offset = 0;
        int32_t code_size = 0;
        int32_t opcode_num = (entry) ? (3) : (5);
        while (read_opcodes < opcode_num) {
            uint8_t tag = code[ip++];
            switch(tag) {
                case INDEX:
                    idx = read_int32(code, ip);
                    read_opcodes++; ip += 4;
                    vm.functions[j].idx = idx;
                    if (entry) {
                        vm.call_stack = malloc(sizeof(Frame));
                        vm.call_stack[0].func_ptr = &vm.functions[1];
                        vm.call_stack[0].ip = 0;
                        vm.call_stack[0].ret_addr = -1;
                    }
                    break;
                case CODE_OFFSET:
                    offset = read_int64(code, ip);
                    ip += 8; read_opcodes++;
                    break;
                case CODE_SIZE:
                    code_size = read_int32(code, ip);
                    ip += 4; read_opcodes++;
                    load_func_bytecode(idx, offset, &vm.functions[idx].code, code_size);
                    break;
                case ARGS: {
                    int32_t arg_num = read_int32(code, ip);
                    ip += 4; read_opcodes++;
                    vm.functions[idx].arg_num = arg_num;
                    vm.functions[idx].args = malloc(sizeof(ValueType) * arg_num);
                    for (int32_t j = 0; j < arg_num; j++) {
                        vm.functions[idx].args[j] = code[ip++];
                    }
                    break;
                }
                case LOCALS: {
                    int32_t local_num = read_int32(code, ip);
                    ip += 4; read_opcodes++;
                    vm.functions[idx].local_num = local_num;
                    vm.functions[idx].locals = malloc(sizeof(ValueType) * local_num);
                    for (int32_t j = 0; j < local_num; j++) {
                        vm.functions[idx].locals[j] = code[ip++];
                    }
                    break;
                }

                default:
                    printf("{%d}", tag);
                    perror("Unknown function tag!");
                    exit(1);

            }
        }
    }
}

// Construct frame table
void construct_frame_table(int64_t addr) {
    int32_t func_count = read_int32(code, addr);
    vm.func_count = func_count;
    vm.functions = malloc(sizeof(Function) * func_count);

    for (int32_t i = 0; i < func_count; i++) {
        vm.functions[i].code = NULL;
        vm.functions[i].args = NULL;
        vm.functions[i].locals = NULL;
    }

    construct_func_table(addr + 4, func_count);
}

// Construct full binary
void ConstructBin() {
    int32_t header_size = read_int32(code, 0);

    int64_t i = 4;
    
    while (i < header_size) {
        switch (code[i++]) {
            case CONSTANTS_TABLE: {
                int64_t table_addr = read_int64(code, i);
                i += 8;
                construct_const_table(table_addr);
                break;
            }

            case GLOBALS_TABLE: {
                int64_t table_addr = read_int64(code, i);
                i += 8;
                construct_global_table(table_addr);
                break;
            }

            case FUNCTIONS_TABLE: {
                int64_t table_addr = read_int64(code, i);
                i += 16;
                construct_frame_table(table_addr);
                break;
            }

            default:
                perror("Unknown Table in header!");
                exit(1);
        }
    }
}