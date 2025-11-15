#include "vm.h"

bool stop() {return true;}

bool push(int16_t addr) {
    push_int(co_consts[addr].value.int_val);
    return false;
}

bool out() {
    if (sp == -1) {
        printf("Nothing in Stack!");
        exit(1);
    }
    printf("%d\n", pop_int());
    return false;
}

bool store(int16_t addr) {
    int32_t store_val = pop_int();
    store_globals(addr, store_val);
    return false;
}

bool load(int16_t addr) {
    int32_t global = get_globals(addr);
    push_int(global);
    return false;
}

bool add() {
    int32_t rhs = pop_int();
    int32_t lhs = pop_int();
    int32_t total = lhs + rhs;
    push_int(total);
    return false;
}

bool sub() {
    int32_t rhs = pop_int();
    int32_t lhs = pop_int();
    int32_t total = lhs - rhs;
    push_int(total);
    return false;
}

bool mul() {
    int32_t rhs = pop_int();
    int32_t lhs = pop_int();
    int32_t total = lhs * rhs;
    push_int(total);
    return false;
}

bool div_() {
    int32_t rhs = pop_int();
    if (rhs == 0) {
        printf("Division by Zero Error!");
        exit(1);
    }
    int32_t lhs = pop_int();
    int32_t total = (int32_t)(lhs / rhs);
    push_int(total);
    return false;
}

bool call(int16_t addr) {
    push_int(fp);
    push_int(ip);
    fp = sp;
    ip = addr;
    return false;
}

bool leave() {
    ip = stack[fp];
    fp = stack[fp - 1];
    sp = fp;
    return false;
}

bool ret() {
    int32_t return_val = pop_int();
    ip = stack[fp];
    fp = stack[fp - 1];
    sp = fp;
    push_int(return_val);
    return false;
}

bool load_a(int16_t addr) {
    push_int(stack[fp - 2 - addr]);
    return false;
}
bool enter(int32_t val) {
    for (int32_t i = 0; i < val; i++) {
        push_int(-1);
    }
    return false;
}

bool load_l(int16_t addr) {
    push_int(stack[fp + 1 + addr]);
    return false;
}

bool store_l(int16_t addr) {
    stack[fp + 1 + addr] = pop_int();
    return false;
    return false;
}

bool jmp(int16_t addr) {
    ip = (ip - (OPCODE_SIZE + OPERAND_SIZE)) + addr;
    return false;
}
