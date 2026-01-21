//#include "vm.h"
#include "execute.h"

bool stop(uint64_t operand) {return true;}

bool push(uint64_t operand) {
    push_val(vm.constants[operand]);
    return false;
}

bool pop(uint64_t operand) {
    pop_val();
    return false;
}

bool dup(uint64_t operand) {
    Value val = pop_val();
    push_val(val);
    push_val(val);
    return false;
}

bool swap(uint64_t operand) {
    Value rhs, lhs;
    rhs = pop_val();
    lhs = pop_val();
    push_val(rhs);
    push_val(lhs);
    return false;
}

bool out(uint64_t operand) {
    if (vm.sp == -1) {
        printf("Nothing in Stack!");
        exit(1);
    }
    Value ans = pop_val();
    printf("OUTPUT: ");
    if (IsInt32(ans.type)) {printf("%d", ans.i32);}
    else if (IsInt64(ans.type)) {printf("%lld", ans.i64);}
    else if (IsBool(ans.type)) {printf("%d", ans.bl);}
    else if (IsChar(ans.type)) {printf("%c", ans.chr);}
    else if (IsR32(ans.type)) {printf("%f", ans.r32);}
    else if (IsR64(ans.type)) {printf("%f", ans.r64);}
    putchar('\n');
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
    if (adjust_overflow(&lhs, &rhs, total.type, add_overflow)) {
        printf("Overflow Error!\n"); exit(1);
    };
    switch (total.type) {
        case INT32: total.i32 = lhs.i32 + rhs.i32; break;
        case INT64: total.i64 = lhs.i64 + rhs.i64; break;
        case REAL32: total.r32 = lhs.r32 + rhs.r32; break;
        case REAL64: total.r64 = lhs.r64 + rhs.r64; break;
        case CHAR: total.chr = lhs.chr + rhs.chr; break;
        case BOOL: total.bl = lhs.bl || rhs.bl; break;
        default: return false;
    }
    push_val(total);
    return false;
}

bool sub(uint64_t operand) {
    Value lhs, rhs, total;
    rhs = pop_val();
    lhs = pop_val();
    total.type = resolve_type(&lhs, &rhs);
    if (adjust_overflow(&lhs, &rhs, total.type, sub_overflow)) {
        printf("Overflow Error!\n"); exit(1);
    };
    switch (total.type) {
        case INT32: total.i32 = lhs.i32 - rhs.i32; break;
        case INT64: total.i64 = lhs.i64 - rhs.i64; break;
        case REAL32: total.r32 = lhs.r32 - rhs.r32; break;
        case REAL64: total.r64 = lhs.r64 - rhs.r64; break;
        case CHAR: total.chr = lhs.chr - rhs.chr; break;
        case BOOL: total.bl = !(lhs.bl || rhs.bl); break;
        default: return false;
    }
    push_val(total);
    return false;
}

bool mul(uint64_t operand) {
    Value lhs, rhs, total;
    rhs = pop_val();
    lhs = pop_val();
    total.type = resolve_type(&lhs, &rhs);
    if (adjust_overflow(&lhs, &rhs, total.type, mul_overflow)) {
        printf("Overflow Error!\n"); exit(1);
    };
    switch (total.type) {
        case INT32: total.i32 = lhs.i32 * rhs.i32; break;
        case INT64: total.i64 = lhs.i64 * rhs.i64; break;
        case REAL32: total.r32 = lhs.r32 * rhs.r32; break;
        case REAL64: total.r64 = lhs.r64 * rhs.r64; break;
        case CHAR: total.chr = lhs.chr * rhs.chr; break;
        case BOOL: total.bl = lhs.bl && rhs.bl; break;
        default: return false;
    }
    push_val(total);
    return false;
}

bool div_(uint64_t operand) {
    Value lhs, rhs, total;
    rhs = pop_val();
    lhs = pop_val();
    bool zero_div = false;
    total.type = resolve_type(&lhs, &rhs);
    if (adjust_overflow(&lhs, &rhs, total.type, div_overflow)) {
        printf("Overflow Error!\n"); exit(1);
    };
    switch (total.type) {
        case INT32: zero_div = rhs.i32 == 0; break;
        case INT64: zero_div = rhs.i64 == 0; break;
        case REAL32: zero_div = rhs.r32 == 0; break;
        case REAL64: zero_div = rhs.r64 == 0; break;
        case CHAR: zero_div = rhs.chr == 0; break;
        case BOOL: break;
        default: break;
    }
    if (zero_div) {
        printf("Zero Div Error!\n"); exit(1);
    }
    switch (total.type) {
        case INT32: total.i32 = lhs.i32 / rhs.i32; break;
        case INT64: total.i64 = lhs.i64 / rhs.i64; break;
        case REAL32: total.r32 = lhs.r32 / rhs.r32; break;
        case REAL64: total.r64 = lhs.r64 / rhs.r64; break;
        case CHAR: total.chr = lhs.chr / rhs.chr; break;
        case BOOL: total.bl = !(lhs.bl && rhs.bl); break;
        default: return false;
    }
    push_val(total);
    return false;
}

bool leave(uint64_t operand) {
    return false;
}

bool enter(uint64_t operand) {
    uint32_t val = vm.constants[operand].i32;
    for (uint64_t i = 0; i < val; i++) {
        push_val((Value) {.type=INT32, .i32=-1});
    }
    return false;
}


bool call(uint64_t operand) {
    push_val((Value) {.type=INT32, .i32=vm.bp});
    vm.bp = vm.sp;
    vm.fp++;
    vm.call_stack = realloc(vm.call_stack, sizeof(Frame)*(vm.fp+1));
    Value func = get_globals(operand);
    if (func.type != OBJ && func.obj.type != OBJ_FUNC) {
        printf("NaF\n"); exit(1);
    }
    vm.call_stack[vm.fp].func_ptr = &func.obj.func_obj;//vm.functions[operand];
    vm.call_stack[vm.fp].ip = 0;
    vm.call_stack[vm.fp].ret_addr = vm.fp-1;
    return enter(vm.call_stack[vm.fp].func_ptr->local_num);
}

bool ret(uint64_t operand) {
    Value return_val = pop_val();
    vm.sp = vm.bp - vm.call_stack[vm.fp].func_ptr->arg_num - 1;
    vm.bp = vm.stack[vm.bp].i32;
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

bool jmp(uint64_t operand) {
    int64_t jmp_addr = (int16_t)operand;
    jmp_addr = vm.call_stack[vm.fp].ip + (jmp_addr - vm.operand_size - WORD);
    vm.call_stack[vm.fp].ip = jmp_addr;
    return false;
}

bool e_size(uint64_t operand) {
    vm.operand_size = operand;
    return false;
}

#define ieq(lhs, rhs) (bool)(lhs == rhs)
#define igt(lhs, rhs) (bool)(lhs > rhs)
#define ilt(lhs, rhs) (bool)(lhs < rhs)
#define igte(lhs, rhs) (bool)(lhs >= rhs)
#define ilte(lhs, rhs) (bool)(lhs <= rhs)
#define ine(lhs, rhs) (bool)(lhs != rhs)

bool ceq(uint64_t operand) {
    Value lhs, rhs, result;
    rhs = pop_val(); 
    lhs = pop_val();
    result.type = BOOL;
    resolve_type(&lhs, &rhs);
    switch (lhs.type) {
        case INT32: result.bl = ieq(lhs.i32, rhs.i32); break;
        case INT64: result.bl = ieq(lhs.i64, rhs.i64); break;
        case REAL32: result.bl = fabs(lhs.r32-rhs.r32) < FLT_EPSILON; break;
        case REAL64: result.bl = fabs(lhs.r64-rhs.r64) < DBL_EPSILON; break;
        case CHAR: result.bl = ieq(lhs.chr, rhs.chr); break;
        case BOOL: result.bl = ieq(lhs.bl, rhs.bl); break;
        default: break;
    }
    push_val(result);
    return false;
}

bool cgt(uint64_t operand) {
    Value lhs, rhs, result;
    rhs = pop_val(); 
    lhs = pop_val();
    result.type = BOOL;
    resolve_type(&lhs, &rhs);
    switch (lhs.type) {
        case INT32: result.bl = igt(lhs.i32, rhs.i32); break;
        case INT64: result.bl = igt(lhs.i64, rhs.i64); break;
        case REAL32: result.bl = lhs.r32-rhs.r32 > FLT_EPSILON; break;
        case REAL64: result.bl = lhs.r64-rhs.r64 > DBL_EPSILON; break;
        case CHAR: result.bl = igt(lhs.chr, rhs.chr); break;
        case BOOL: result.bl = igt(lhs.bl, rhs.bl); break;
        default: break;
    }
    push_val(result);
    return false;
}

bool clt(uint64_t operand) {
    Value lhs, rhs, result;
    rhs = pop_val(); 
    lhs = pop_val();
    result.type = BOOL;
    resolve_type(&lhs, &rhs);
    switch (lhs.type) {
        case INT32: result.bl = ilt(lhs.i32, rhs.i32); break;
        case INT64: result.bl = ilt(lhs.i64, rhs.i64); break;
        case REAL32: result.bl = rhs.r32-lhs.r32 > FLT_EPSILON; break;
        case REAL64: result.bl = rhs.r64-lhs.r64 > DBL_EPSILON; break;
        case CHAR: result.bl = ilt(lhs.chr, rhs.chr); break;
        case BOOL: result.bl = ilt(lhs.bl, rhs.bl); break;
        default: break;
    }
    push_val(result);
    return false;
}

bool cgte(uint64_t operand) {
    Value lhs, rhs, result;
    rhs = pop_val(); 
    lhs = pop_val();
    result.type = BOOL;
    resolve_type(&lhs, &rhs);
    switch (lhs.type) {
        case INT32: result.bl = igte(lhs.i32, rhs.i32); break;
        case INT64: result.bl = igte(lhs.i64, rhs.i64); break;
        case REAL32: result.bl = lhs.r32-rhs.i32 > -FLT_EPSILON; break;
        case REAL64: result.bl = lhs.r64-rhs.i64 > -DBL_EPSILON; break;
        case CHAR: result.bl = igte(lhs.chr, rhs.chr); break;
        case BOOL: result.bl = igte(lhs.bl, rhs.bl); break;
        default: break;
    }
    push_val(result);
    return false;
}

bool clte(uint64_t operand) {
    Value lhs, rhs, result;
    rhs = pop_val(); 
    lhs = pop_val();
    result.type = BOOL;
    resolve_type(&lhs, &rhs);
    switch (lhs.type) {
        case INT32: result.bl = ilte(lhs.i32, rhs.i32); break;
        case INT64: result.bl = ilte(lhs.i64, rhs.i64); break;
        case REAL32: result.bl = rhs.r32-lhs.r32 > -FLT_EPSILON; break;
        case REAL64: result.bl = rhs.r64-lhs.r64 > -DBL_EPSILON; break;
        case CHAR: result.bl = ilte(lhs.chr, rhs.chr); break;
        case BOOL: result.bl = ilte(lhs.bl, rhs.bl); break;
        default: break;
    }
    push_val(result);
    return false;
}

bool cne(uint64_t operand) {
    Value lhs, rhs, result;
    rhs = pop_val(); 
    lhs = pop_val();
    result.type = BOOL;
    resolve_type(&lhs, &rhs);
    switch (lhs.type) {
        case INT32: result.bl = ine(lhs.i32, rhs.i32); break;
        case INT64: result.bl = ine(lhs.i64, rhs.i64); break;
        case REAL32: result.bl = fabs(rhs.r32-lhs.r32) > FLT_EPSILON; break;
        case REAL64: result.bl = fabs(rhs.r64-lhs.r64) > DBL_EPSILON; break;
        case CHAR: result.bl = ine(lhs.chr, rhs.chr); break;
        case BOOL: result.bl = ine(lhs.bl, rhs.bl); break;
        default: break;
    }
    push_val(result);
    return false;
}

bool jpt(uint64_t operand) {
    Value val = pop_val();
    if (val.type == BOOL && val.bl) {
        return jmp(operand);
    } else {
        to_bl(&val);
        if (val.bl) {
            return jmp(operand);
        }
    }
    return false;
}

bool jpf(uint64_t operand) {
    Value val = pop_val();
    if (val.type == BOOL && !val.bl) {
        return jmp(operand);
    } else {
        to_bl(&val);
        if (!val.bl) {
            return jmp(operand);
        }
    }
    return false;
}

static void lhs_rhs_bl(Value* lhs, Value* rhs) {
    if (lhs->type == rhs->type == BOOL) {return;}
    to_bl(lhs); to_bl(rhs);
}

bool f_and(uint64_t operand) {
    Value lhs, rhs, result;
    rhs = pop_val();
    lhs = pop_val();
    result.type = BOOL;
    lhs_rhs_bl(&lhs, &rhs);
    result.bl = lhs.bl && rhs.bl;
    push_val(result);
    return false;
}

bool f_or(uint64_t operand) {
    Value lhs, rhs, result;
    rhs = pop_val();
    lhs = pop_val();
    result.type = BOOL;
    lhs_rhs_bl(&lhs, &rhs);
    result.bl = lhs.bl || rhs.bl;
    push_val(result);
    return false;
}

bool f_not(uint64_t operand) {
    Value val, result;
    val = pop_val();
    result.type = BOOL;
    if (val.type != BOOL) to_bl(&val);
    result.bl = !val.bl;
    push_val(result);
    return false;
}

bool fb_ls(uint64_t operand) {
    Value lhs, rhs, result;
    rhs = pop_val();
    lhs = pop_val();
    result.type = lhs.type;
    to_i32(&rhs);
    switch (result.type) {
        case INT32: result.i32 <<= rhs.i32; break;
        case INT64: result.i64 <<= rhs.i32; break;
        case CHAR: result.chr <<= rhs.i32; break;
        case REAL32:
        case REAL64:
        case BOOL: printf("NOT VALID WITH LEFT SHIFT\n"); break;
        default: result.type=NONE; break;
    }
    push_val(result);
    return false;
}

bool fb_rs(uint64_t operand) {
    Value lhs, rhs, result;
    rhs = pop_val();
    lhs = pop_val();
    result = lhs;
    to_i32(&rhs);
    switch (result.type) {
        case INT32: result.i32 >>= rhs.i32; break;
        case INT64: result.i64 >>= rhs.i32; break;
        case CHAR: result.chr >>= rhs.i32; break;
        case REAL32:
        case REAL64:
        case BOOL: printf("NOT VALID WITH RIGHT SHIFT\n"); break;
        default: result.type=NONE; break;
    }
    push_val(result);
    return false;
}

bool fb_and(uint64_t operand) {
    Value lhs, rhs, result;
    rhs = pop_val();
    lhs = pop_val();
    result.type = resolve_type(&lhs, &rhs);
    switch (result.type) {
        case INT32: result.i32 = lhs.i32 & rhs.i32; break;
        case INT64: result.i64 = lhs.i64 & rhs.i64; break;
        case CHAR: result.chr = lhs.chr & rhs.chr; break;
        case BOOL: result.bl = lhs.bl & rhs.bl; break;
        case REAL32: case REAL64: printf("MUST HAVE INTEGRAL TYPE FOR BITWISE AND\n"); exit(1);
        default: return false;
    }
    push_val(result);
    return false;
}

bool fb_or(uint64_t operand) {
    Value lhs, rhs, result;
    rhs = pop_val();
    lhs = pop_val();
    result.type = resolve_type(&lhs, &rhs);
    switch (result.type) {
        case INT32: result.i32 = lhs.i32 | rhs.i32; break;
        case INT64: result.i64 = lhs.i64 | rhs.i64; break;
        case CHAR: result.chr = lhs.chr | rhs.chr; break;
        case BOOL: result.bl = lhs.bl | rhs.bl; break;
        case REAL32: case REAL64: printf("MUST HAVE INTEGRAL TYPE FOR BITWISE OR\n"); exit(1);
        default: return false;
    }
    push_val(result);
    return false;
}

bool fb_xor(uint64_t operand) {
    Value lhs, rhs, result;
    rhs = pop_val();
    lhs = pop_val();
    result.type = resolve_type(&lhs, &rhs);
    switch (result.type) {
        case INT32: result.i32 = lhs.i32 ^ rhs.i32; break;
        case INT64: result.i64 = lhs.i64 ^ rhs.i64; break;
        case CHAR: result.chr = lhs.chr ^ rhs.chr; break;
        case BOOL: result.bl = lhs.bl ^ rhs.bl; break;
        case REAL32: case REAL64: printf("MUST HAVE INTEGRAL TYPE FOR BITWISE XOR\n"); exit(1);
        default: return false;
    }
    push_val(result);
    return false;
}

bool fb_not(uint64_t operand) {
    Value val, result;
    val = pop_val();
    result.type = val.type;
    switch (result.type) {
        case INT32: result.i32 = ~val.i32; break;
        case INT64: result.i64 = ~val.i64; break;
        case CHAR: result.chr = ~val.chr; break;
        case BOOL: result.bl = !val.bl; break;
        case REAL32: case REAL64: printf("MUST HAVE INTEGRAL TYPE FOR BITWISE NOT\n"); exit(1);
        default: return false;
    }
    push_val(result);
    return false;
}
