#include "tree_walker.h"

Value evaluate(Expr* expr);

void to_double(Value* val) {
    switch(val->type) {
        case INT32: val->value.r64 = (double)val->value.i32; break;
        case REAL32: return;
        case BOOL: val->value.r64 = (double)val->value.bl; break;
        case CHAR: val->value.r64 = (double)val->value.chr; break;
        default: printf("Invalid Castin!\n"); exit(1);
        //case S: val->value.r = (double)val->value.i;
    }
    val->type = REAL64;
}

double get_double(Value val) {
    switch(val.type) {
        case INT32: return (double)val.value.i32;
        case REAL64: return val.value.r64;
        case BOOL: return (double)val.value.bl;
        case CHAR: return (double)val.value.chr;
        default: printf("Invalid Castin!\n"); exit(1);
        //case S: val->value.r = (double)val->value.i;
    }
}

Value make_obj(double value) {
    return ((Value) {.type=REAL64, .value.r64=value});
}

Value isEqual(Value left, Value right) {
    if (left.type==NONE && right.type==NONE) return (Value) {.type=BOOL, .value.bl=true};
    if (left.type==NONE || right.type==NONE) return (Value) {.type=BOOL, .value.bl=false};
    return (Value) {.type=BOOL, .value.bl=(get_double(left) == get_double(right))};
}

bool isTruthy(Value val) {
    if (val.type == NONE) return false;
    if (val.type == BOOL) return val.value.bl;
    return true;
}

Value visit_unary(Unary expr) {
    Value right = evaluate(expr.right);
    switch (expr.type.type) {
        case BANG:
            return (Value){.type=BOOL, .value.bl=isTruthy(right)};
        case MINUS: 
            to_double(&right);
            right.value.r64 = -right.value.r64;
            return right;
        default: break;
    }
    return (Value) {.type=NONE};
}

Value visit_literal(Value expr) {
    return expr;
}

Value visit_grouping(Grouping expr) {
    return evaluate(expr.expression);
}

Value visit_binary(Binary expr) {
    Value left = evaluate(expr.left);
    Value right = evaluate(expr.right);

    switch (expr.type.type) {
        case MINUS:
            return make_obj(get_double(left) - get_double(right));
        case SLASH:
            return make_obj(get_double(left) / get_double(right));
        case STAR:
            return make_obj(get_double(left) * get_double(right));
        case PLUS:
            if ((left.type == OBJ && left.value.obj.type == STR) && (right.type == OBJ && right.value.obj.type == STR)) {
                char str[512];
                sprintf(str, "%s%s", left.value.obj.str_obj.str, right.value.obj.str_obj.str);
                return ((Value) {.type=OBJ, .value.obj.str_obj.str=str, .value.obj.type=STR});
            } else {
                return make_obj(get_double(left) + get_double(right));
            }
        case GREATER:
            return make_obj(get_double(left) > get_double(right));
        case GREATER_EQUAL:
            return make_obj(get_double(left) >= get_double(right));
        case LESS:
            return make_obj(get_double(left) < get_double(right));
        case LESS_EQUAL:
            return make_obj(get_double(left) <= get_double(right));
        case BANG_EQUAL:
            return ((Value){.type=BOOL, .value.bl=!isEqual(left, right).value.bl});
        case EQUAL:
            return isEqual(left, right);
        default:
            printf("Unknown in binary!!!"); exit(1);
    }

    return (Value) {.type=NONE};
}

Value evaluate(Expr* expr) {
    switch (expr->type) {
        case GROUPING: return visit_grouping(expr->group);
        case BINARY: return visit_binary(expr->binary);
        case LITERAL: return visit_literal(expr->literal);
        case UNARY: return visit_unary(expr->unary);
        default: return (Value) {.type=NONE};
    }
    return (Value) {.type=NONE};
}

void visit_expression(Expr* expr) {
    evaluate(expr);
}

void visit_print(Expr* expr) {
    Value final_value = evaluate(expr);
    switch (final_value.type) {
        case REAL64: printf("Output: %02f\n", final_value.value.r64); return;
        case BOOL: printf("Output: %s\n", final_value.value.bl ? "TRUE" : "FALSE"); return;
        case OBJ: if (final_value.value.obj.type == STR) {printf("Ouput: %s\n", final_value.value.obj.str_obj.str);}; return;
        default: return;
    }
}

void Walker(Stmt*** tree, uint32_t num) {
    for (uint32_t i = 0; i < num; i++) {
        switch ((*tree)[i]->type) {
            case EXPR: visit_expression((*tree)[i]->expr); break;
            case PRINT: visit_print((*tree)[i]->out_stmt); break;
        }
    }
}