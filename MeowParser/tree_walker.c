#include "tree_walker.h"

Object evaluate(Expr* expr);

void to_double(Object* val) {
    switch(val->type) {
        case I: val->value.r = (double)val->value.i; break;
        case R: return;
        case B: val->value.r = (double)val->value.b; break;
        case C: val->value.r = (double)val->value.c; break;
        default: printf("Invalid Castin!\n"); exit(1);
        //case S: val->value.r = (double)val->value.i;
    }
    val->type = R;
}

double get_double(Object val) {
    switch(val.type) {
        case I: return (double)val.value.i;
        case R: return val.value.r;
        case B: return (double)val.value.b;
        case C: return (double)val.value.c;
        default: printf("Invalid Castin!\n"); exit(1);
        //case S: val->value.r = (double)val->value.i;
    }
}

Object make_obj(double value) {
    return ((Object) {.type=R, .value.r=value});
}

Object isEqual(Object left, Object right) {
    if (left.type==N && right.type==N) return (Object) {.type=B, .value.b=true};
    if (left.type==N || right.type==N) return (Object) {.type=B, .value.b=false};
    return (Object) {.type=B, .value.b=(get_double(left) == get_double(right))};
}

bool isTruthy(Object val) {
    if (val.type == N) return false;
    if (val.type == B) return val.value.b;
    return true;
}

Object visit_unary(Unary expr) {
    Object right = evaluate(expr.right);
    switch (expr.type.type) {
        case BANG:
            return (Object){.type=B, .value.b=isTruthy(right)};
        case MINUS: 
            to_double(&right);
            right.value.r = -right.value.r;
            return right;
        default: break;
    }
    return (Object) {.type=N};
}

Object visit_literal(Object expr) {
    return expr;
}

Object visit_grouping(Grouping expr) {
    return evaluate(expr.expression);
}

Object visit_binary(Binary expr) {
    Object left = evaluate(expr.left);
    Object right = evaluate(expr.right);

    switch (expr.type.type) {
        case MINUS:
            return make_obj(get_double(left) - get_double(right));
        case SLASH:
            return make_obj(get_double(left) / get_double(right));
        case STAR:
            return make_obj(get_double(left) * get_double(right));
        case PLUS:
            if (left.type == S && right.type == S) {
                char str[512];
                sprintf(str, "%s%s", left.value.s, right.value.s);
                return ((Object) {.type=S, .value.s=str});
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
            return ((Object){.type=B, .value.b=!isEqual(left, right).value.b});
        case EQUAL:
            return isEqual(left, right);
        default:
            printf("Unknown in binary!!!"); exit(1);
    }

    return (Object) {.type=N};
}

Object evaluate(Expr* expr) {
    switch (expr->type) {
        case GROUPING: return visit_grouping(expr->group);
        case BINARY: return visit_binary(expr->binary);
        case LITERAL: return visit_literal(expr->literal);
        case UNARY: return visit_unary(expr->unary);
        default: return (Object) {.type=N};
    }
    return (Object) {.type=N};
}

void Walker(Expr* tree) {
    Object final_value = evaluate(tree);
    switch (final_value.type) {
        case R: printf("Output: %02f\n", final_value.value.r); return;
        case B: printf("Output: %s\n", final_value.value.b ? "TRUE" : "FALSE"); return;
        case S: printf("Ouput: %s\n", final_value.value.s); return;
        default: return;
    }
}