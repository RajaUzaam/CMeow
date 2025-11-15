#include "vm.h"

bool stop() {return true;}

bool push(int16_t addr) {
    push_int(co_consts[addr]);
    return false;
}

bool out() {
    if (vm.sp == -1) {
        printf("Nothing in Stack!");
        exit(1);
    }
    printf("%d\n", pop_int().value.int_val);
    return false;
}

bool store(int16_t addr) {
    Value store_val = pop_int();
    store_globals(addr, store_val);
    return false;
}

bool load(int16_t addr) {
    Value global = get_globals(addr);
    push_int(global);
    return false;
}

bool add() {
    int32_t rhs = pop_int().value.int_val;
    int32_t lhs = pop_int().value.int_val;
    int32_t total = lhs + rhs;
    push_int((Value){.type=INT32, .value.int_val=total});
    return false;
}

bool sub() {
    int32_t rhs = pop_int().value.int_val;
    int32_t lhs = pop_int().value.int_val;
    int32_t total = lhs - rhs;
    push_int((Value){.type=INT32, .value.int_val=total});
    return false;
}

bool mul() {
    int32_t rhs = pop_int().value.int_val;
    int32_t lhs = pop_int().value.int_val;
    int32_t total = lhs * rhs;
    push_int((Value){.type=INT32, .value.int_val=total});
    return false;
}

bool div_() {
    int32_t rhs = pop_int().value.int_val;
    if (rhs == 0) {
        printf("Division by Zero Error!");
        exit(1);
    }
    int32_t lhs = pop_int().value.int_val;
    int32_t total = (int32_t)(lhs / rhs);
    push_int((Value) {.type = INT32, .value.int_val = total});
    return false;
}

bool call(int16_t addr) {
    printf("CALLED!\n");
    push_int((Value) {.type=INT32, .value.int_val=vm.bp});
    vm.bp = vm.sp;
    //push_int(vm.call_stack[vm.fp].ip);
    vm.fp++;
    vm.call_stack = realloc(vm.call_stack, sizeof(Frame)*(vm.fp+1));
    //vm.fp = vm.sp;
    vm.call_stack[vm.fp].func_ptr = &vm.functions[addr];
    vm.call_stack[vm.fp].ip = 0;
    vm.call_stack[vm.fp].ret_addr = vm.fp-1;
    return false;
}

bool leave() {
    // ip = stack[fp];
    // fp = stack[fp - 1];
    // sp = fp;
    return false;
}

bool ret() {
    Value return_val = pop_int();
    //ip = stack[fp];
    vm.fp--;
    vm.sp = vm.bp;
    vm.bp = vm.stack[vm.bp].value.int_val;
    //fp = stack[fp - 1];
    //sp = fp;
    push_int(return_val);
    return false;
}

bool load_a(int16_t addr) {
    push_int(vm.stack[vm.bp - 1 - addr]);//stack[fp - 2 - addr]);
    return false;
}
bool enter(int32_t val) {
    printf("ENTER! %d\n", val);
    for (int32_t i = 0; i < val; i++) {
        push_int((Value) {.type=INT32, .value.int_val=0});
    }
    printf("ENTERED\n");
    return false;
}

bool load_l(int16_t addr) {
    int32_t to_push = vm.stack[vm.bp + 1 + addr].value.int_val;
    printf("TO LOADL: %d\n", to_push);
    push_int(vm.stack[vm.bp + 1 + addr]);
    return false;
}

bool store_l(int16_t addr) {
    printf("STORING... | %d\n", addr);
    Value to_store = pop_int();
    printf("Store Val: %d\n", to_store.value.int_val);
    vm.stack[vm.bp + 1 + addr] = to_store;
    return false;
}

bool jmp(int16_t addr) {
    //ip = (ip - (OPCODE_SIZE + OPERAND_SIZE)) + addr;
    //vmip = 
    vm.call_stack[vm.fp].ip = (vm.call_stack[vm.fp].ip - (OPCODE_SIZE + OPERAND_SIZE)) + addr;
    return false;
}
