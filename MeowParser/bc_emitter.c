#include "bc_emitter.h"

void evaluate(Expr* expr);

// void to_double(Value* val) {
//     switch(val->type) {
//         case INT32: val->value.r64 = (double)val->value.i32; break;
//         case REAL32: return;
//         case BOOL: val->value.r64 = (double)val->value.bl; break;
//         case CHAR: val->value.r64 = (double)val->value.chr; break;
//         default: printf("Invalid Castin!\n"); exit(1);
//         //case S: val->value.r = (double)val->value.i;
//     }
//     val->type = REAL64;
// }

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

void negate(Value* val) {
    switch(val->type) {
        case INT32: val->value.i32 = -val->value.i32; break;
        case REAL32: val->value.r32 = -val->value.r32; break;
        case CHAR: val->value.chr = -val->value.chr; break;
        case INT64: val->value.i64 = -val->value.i64; break;
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

void visit_unary(Unary expr) {
    evaluate(expr.right);
    switch (expr.type.type) {
        case BANG: break;
            //return (Value){.type=BOOL, .value.bl=isTruthy(right)};
        case MINUS: 
            //to_double(&right);
            //right.value.r64 = -right.value.r64;
            //negate(&right);
            //add_constant(right);
            add_constant((Value){.type=INT32, .value.i32=-1,});
            add_opcode(MUL);
            //return right;
        default: break;
    }
    //return (Value) {.type=NONE};
}

void visit_literal(Value expr) {
    add_constant(expr);
    //return expr;
}

void visit_grouping(Grouping expr) {
    evaluate(expr.expression);
}

void visit_binary(Binary expr) {
    evaluate(expr.left);
    evaluate(expr.right);

    switch (expr.type.type) {
        case MINUS:
            add_opcode(SUB); return;
            //return make_obj(get_double(left) - get_double(right));
        case SLASH:
            add_opcode(DIV); return;
            //return make_obj(get_double(left) / get_double(right));
        case STAR:
            add_opcode(MUL); return;
            //return make_obj(get_double(left) * get_double(right));
        case PLUS:
            add_opcode(ADD); return;
            // if ((left.type == OBJ && left.value.obj.type == STR) && (right.type == OBJ && right.value.obj.type == STR)) {
            //     char str[512];
            //     sprintf(str, "%s%s", left.value.obj.str_obj.str, right.value.obj.str_obj.str);
            //     return ((Value) {.type=OBJ, .value.obj.str_obj.str=str, .value.obj.type=STR});
            // } else {
            //     return make_obj(get_double(left) + get_double(right));
            // }
        // case GREATER:
        //     return make_obj(get_double(left) > get_double(right));
        // case GREATER_EQUAL:
        //     return make_obj(get_double(left) >= get_double(right));
        // case LESS:
        //     return make_obj(get_double(left) < get_double(right));
        // case LESS_EQUAL:
        //     return make_obj(get_double(left) <= get_double(right));
        // case BANG_EQUAL:
        //     return ((Value){.type=BOOL, .value.bl=!isEqual(left, right).value.bl});
        // case EQUAL:
        //     return isEqual(left, right);
        default:
            printf("Unknown in binary!!!"); exit(1);
    }
    add_constant((Value) {.type=NONE});
    //return (Value) {.type=NONE};
}

void evaluate(Expr* expr) {
    switch (expr->type) {
        case GROUPING: visit_grouping(expr->group); return;
        case BINARY: visit_binary(expr->binary); return;
        case LITERAL: visit_literal(expr->literal); return;
        case UNARY: visit_unary(expr->unary); return;
        default: break;
    }
    add_constant((Value) {.type=NONE});
}

void visit_expression(Expr* expr) {
    evaluate(expr);
}

void visit_print(Expr* expr) {
    evaluate(expr);
    add_opcode(OUT);
    // switch (final_value.type) {
    //     case REAL64: printf("Output: %02f\n", final_value.value.r64); return;
    //     case BOOL: printf("Output: %s\n", final_value.value.bl ? "TRUE" : "FALSE"); return;
    //     case OBJ: if (final_value.value.obj.type == STR) {printf("Ouput: %s\n", final_value.value.obj.str_obj.str);}; return;
    //     default: return;
    // }
}

void Emitter(Stmt*** tree, uint32_t num) {
    for (uint32_t i = 0; i < num; i++) {
        switch ((*tree)[i]->type) {
            case EXPR: visit_expression((*tree)[i]->expr); break;
            case PRINT: visit_print((*tree)[i]->out_stmt); break;
        }
    }
}
