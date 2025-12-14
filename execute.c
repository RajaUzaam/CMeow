#include "vm.h"

bool stop() {return true;}

bool push(uint64_t addr) {
    push_val(co_consts[addr]);
    return false;
}

bool out() {
    if (vm.sp == -1) {
        printf("Nothing in Stack!");
        exit(1);
    }
    Value ans = pop_val();
    printf("OUTPUT: ");
    if (IsInt32(ans.type)) {printf("%d", ans.value.i32);}
    else if (IsInt64(ans.type)) {printf("%lld", ans.value.i64);}
    else if (IsBool(ans.type)) {printf("%d", ans.value.bl);}
    else if (IsChar(ans.type)) {printf("%c", ans.value.chr);}
    else if (IsR32(ans.type)) {printf("%f", ans.value.r32);}
    else if (IsR64(ans.type)) {printf("%f", ans.value.r64);}
    putchar('\n');
    push_val(ans);
    return false;
}

bool store(uint64_t addr) {
    Value store_val = pop_val();
    store_globals(addr, store_val);
    return false;
}

bool load(uint64_t addr) {
    Value global = get_globals(addr);
    push_val(global);
    return false;
}

bool add() {
    Value total;
    perform_operation(&total, OPADD);
    push_val(total);
    return false;
}

bool sub() {
    Value total;
    perform_operation(&total, OPSUB);
    push_val(total);
    return false;
}

bool mul() {
    Value total;
    perform_operation(&total, OPMUL);
    push_val(total);
    return false;
}

bool div_() {
    Value total;
    perform_operation(&total, OPDIV);
    push_val(total);
    return false;
}

bool leave() {
    return false;
}

bool call(uint64_t addr) {
    push_val((Value) {.type=INT32, .value.i32=vm.bp});
    vm.bp = vm.sp;
    vm.fp++;
    vm.call_stack = realloc(vm.call_stack, sizeof(Frame)*(vm.fp+1));
    vm.call_stack[vm.fp].func_ptr = &vm.functions[addr];
    vm.call_stack[vm.fp].ip = 0;
    vm.call_stack[vm.fp].ret_addr = vm.fp-1;
    return false;
}

bool ret() {
    Value return_val = pop_val();
    vm.sp = vm.bp - vm.call_stack[vm.fp].func_ptr->arg_num - 1;
    vm.bp = vm.stack[vm.bp].value.i32;
    vm.fp--;
    push_val(return_val);
    return false;
}

bool load_a(uint64_t addr) {
    push_val(vm.stack[vm.bp - 1 - addr]);
    return false;
}
bool enter(uint64_t val) {
    for (uint64_t i = 0; i < val; i++) {
        push_val((Value) {.type=INT32, .value.i32=-1});
    }
    return false;
}

bool load_l(uint64_t addr) {
    Value to_push = vm.stack[vm.bp + 1 + addr];
    push_val(to_push);
    return false;
}

bool store_l(uint64_t addr) {
    Value to_store = pop_val();
    vm.stack[vm.bp + 1 + addr] = to_store;
    return false;
}

uint64_t ipow(uint64_t base, uint64_t exp) {
    uint64_t result = 1;
    while (exp) {
        if (exp & 1) result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

bool jmp(uint64_t addr) {
    int64_t jmp_addr = ((int64_t) (-1 * ipow(2, 8*OPERAND_SIZE))) + addr;
    vm.call_stack[vm.fp].ip = (vm.call_stack[vm.fp].ip - (OPCODE_SIZE + OPERAND_SIZE)) + (jmp_addr);
    return false;
}
