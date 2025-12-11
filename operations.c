#include "vm.h"

void perform_operation(Value *total, BinaryOps oper) {
    Value rhs, lhs;
    ValueType ans_type;
    rhs = pop_val();
    lhs = pop_val();
    ans_type = (ValueType) max(rhs.type, lhs.type);
    total->type = ans_type;
    promote(&rhs, &ans_type);
    promote(&lhs, &ans_type);
    if (IsInt(ans_type)) {
        switch (oper) {
            case OPADD: total->value.i64 = lhs.value.i64 + rhs.value.i64; break;
            case OPSUB: total->value.i64 = lhs.value.i64 - rhs.value.i64; break;
            case OPMUL: total->value.i64 = lhs.value.i64 * rhs.value.i64; break;
            case OPDIV: 
                if (rhs.value.i64 == 0) {printf("ZeroDiv!\n"); exit(1);}
                total->value.i64 = lhs.value.i64 / rhs.value.i64; break;
            default: printf("Unknown Binary Operation!\n"); exit(1);
        }
    }
    else if (IsReal(ans_type)) {
        switch (oper) {
            case OPADD: total->value.r64 = lhs.value.r64 + rhs.value.r64; break;
            case OPSUB: total->value.r64 = lhs.value.r64 - rhs.value.r64; break;
            case OPMUL: total->value.r64 = lhs.value.r64 * rhs.value.r64; break;
            case OPDIV: 
                if (rhs.value.r64 == 0.0) {printf("ZeroDiv!\n"); exit(1);}
                total->value.r64 = lhs.value.r64 / rhs.value.r64; break;
            default: printf("Unknown Binary Operation!\n"); exit(1);
        }
    }
    cast_type(total, ans_type);
}