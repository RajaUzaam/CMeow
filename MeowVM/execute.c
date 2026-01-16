#include "vm.h"

bool stop(uint64_t operand) {return true;}

bool push(uint64_t operand) {
    push_val(co_consts[operand]);
    return false;
}

bool out(uint64_t operand) {
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

bool store(uint64_t operand) {
    Value store_val = pop_val();
    store_globals(operand, store_val);
    return false;
}

bool load(uint64_t operand) {
    Value global = get_globals(operand);
    push_val(global);
    return false;
}

bool add(uint64_t operand) {
    Value lhs, rhs, total;
    rhs = pop_val();
    lhs = pop_val();
    total.type = resolve_type(&lhs, &rhs);
    switch (total.type) {
        case INT32: total.value.i32 = lhs.value.i32 + rhs.value.i32; break;
        case INT64: total.value.i64 = lhs.value.i64 + rhs.value.i64; break;
        case REAL32: total.value.r32 = lhs.value.r32 + rhs.value.r32; break;
        case REAL64: total.value.r64 = lhs.value.r64 + rhs.value.r64; break;
        case CHAR: total.value.chr = lhs.value.chr + rhs.value.chr; break;
        case BOOL: total.value.bl = lhs.value.bl || rhs.value.bl; break;
        default: return false;
    }
    //perform_operation(&total, OPADD);
    push_val(total);
    return false;
}

bool sub(uint64_t operand) {
    Value total;
    perform_operation(&total, OPSUB);
    push_val(total);
    return false;
}

bool mul(uint64_t operand) {
    Value total;
    perform_operation(&total, OPMUL);
    push_val(total);
    return false;
}

bool div_(uint64_t operand) {
    Value total;
    perform_operation(&total, OPDIV);
    push_val(total);
    return false;
}

bool leave(uint64_t operand) {
    return false;
}

bool enter(uint64_t operand) {
    uint32_t val = co_consts[operand].value.i32;
    for (uint64_t i = 0; i < val; i++) {
        push_val((Value) {.type=INT32, .value.i32=-1});
    }
    return false;
}


bool call(uint64_t operand) {
    push_val((Value) {.type=INT32, .value.i32=vm.bp});
    vm.bp = vm.sp;
    vm.fp++;
    vm.call_stack = realloc(vm.call_stack, sizeof(Frame)*(vm.fp+1));
    vm.call_stack[vm.fp].func_ptr = &vm.functions[operand];
    vm.call_stack[vm.fp].ip = 0;
    vm.call_stack[vm.fp].ret_addr = vm.fp-1;
    return false;
    // return enter(vm.call_stack[vm.fp].func_ptr->locals_num);
}

bool ret(uint64_t operand) {
    Value return_val = pop_val();
    vm.sp = vm.bp - vm.call_stack[vm.fp].func_ptr->arg_num - 1;
    vm.bp = vm.stack[vm.bp].value.i32;
    vm.fp--;
    push_val(return_val);
    return false;
}

bool load_a(uint64_t operand) {
    push_val(vm.stack[vm.bp - 1 - operand]);
    return false;
}

bool load_l(uint64_t operand) {
    Value to_push = vm.stack[vm.bp + 1 + operand];
    push_val(to_push);
    return false;
}

bool store_l(uint64_t operand) {
    Value to_store = pop_val();
    vm.stack[vm.bp + 1 + operand] = to_store;
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

bool jmp(uint64_t operand) {
    int64_t jmp_addr = ((int64_t) (-(GET_BIT(operand, (operand_size*32)-1)) * ipow(2, 8*operand_size))) + operand;
    vm.call_stack[vm.fp].ip = (vm.call_stack[vm.fp].ip - (WORD*5)) + (jmp_addr);
    return false;
}

bool e_size(uint64_t operand) {
    operand_size = operand;
    return false;
}

// #define feq(lhs, rhs) (bool)(lhs == rhs)
// #define fgt(lhs, rhs) (bool)(lhs > rhs)
// #define flt(lhs, rhs) (bool)(lhs < rhs)
// #define fgte(lhs, rhs) (bool)(lhs >= rhs)
// #define flte(lhs, rhs) (bool)(lhs <= rhs)
// #define fne(lhs, rhs) (bool)(lhs != rhs)


// // [1, 2, 3]
// bool eq(uint64_t operand) {
//     Value rhs = pop_val();
//     Value lhs = pop_val();
//     //promote()
//     return false;
// }