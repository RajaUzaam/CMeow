#include "linker.h"

Value* data;
uint64_t data_size;

Value* constants;
uint64_t constants_size;

Function **functions;
uint64_t func_count;

void add_code(uint8_t val) {
    functions[0]->code = realloc(functions[0]->code, sizeof(uint8_t) * (++(functions[0]->code_size)));
}

void add_instr(Opcodes opcode, uint64_t operand, size_t bytes) {
    add_code(opcode); add_code(operand);
}

void add_opcode(Opcodes opcode) {
    add_code(opcode);
}

uint64_t get_constant(Value constant) {
    bool found = false;
    uint64_t i = -1;
    Value constant_element;
    while (!found && ((i+1) < constants_size)) {
        i++;
        constant_element = constants[i];
        switch(constant_element.type) {
            case INT32: {found = constant.i32 == constant_element.i32;}; break;
            default: break;
        }
    }
    i = found ? i : -1;
    return i;
}

void add_constant(Value constant) {
    if (get_constant(constant) != (uint64_t)-1) {
        constants = realloc(constants, sizeof(Value) * ++constants_size);
        constants[constants_size-1] = constant;
    }
}

void push_constant(Value constant) {
    add_constant(constant);
    add_instr(PUSH, get_constant(constant), 1);
}

void add_global(char* name, ValueType type) {

}

void new_function(char* function_name) {

}

void add_func_arg(char* func_name, char* arg, ValueType type) {

}

void add_func_local(char* func_name, char* local, ValueType type) {

}

void func_var(Opcodes opcode, char* var_name) {

}

void add_global_instr() {

}

void add_cf(Opcodes cf) {
    
}

void initialize_linker() {
    functions = malloc(sizeof(Function*));
    functions[0] = malloc(sizeof(Function));
    functions[0]->code = NULL;
    functions[0]->code_size = 0;
    functions[0]->args = NULL;
    functions[0]->arg_num = 0;
    functions[0]->locals = NULL;
    functions[0]->local_num = 0;
    functions[0]->idx = 0;
}

void initiate_linking() {
    
}