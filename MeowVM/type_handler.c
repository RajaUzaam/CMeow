#include "type_handler.h"

void to_i32(Value *val) {
    switch(val->type) {
        case INT32:  return;
        case INT64:  val->i32 = (int32_t) val->i64; break;
        case BOOL:   val->i32 = (int32_t) val->bl; break;
        case CHAR:   val->i32 = (int32_t) val->chr; break;
        case REAL32: val->i32 = (int32_t) val->r32; break;
        case REAL64: val->i32 = (int32_t) val->r64; break;
        default:     return;
    }
    val->type = INT32;
}

void to_i64(Value *val) {
    switch(val->type) {
        case INT32:  val->i64 = (int64_t) val->i32; break;
        case INT64:  return;
        case BOOL:   val->i64 = (int64_t) val->bl; break;
        case CHAR:   val->i64 = (int64_t) val->chr; break;
        case REAL32: val->i64 = (int64_t) val->r32; break;
        case REAL64: val->i64 = (int64_t) val->r64; break;
        default:     return;
    }
    val->type = INT64;
}

void to_r32(Value *val) {
    switch(val->type) {
        case INT32:  val->r32 = (float) val->i32; break;
        case INT64:  val->r32 = (float) val->i64; break;
        case BOOL:   val->r32 = (float) val->bl; break;
        case CHAR:   val->r32 = (float) val->chr; break;
        case REAL32: return;
        case REAL64: val->r32 = (float) val->r64; break;
        default:     return;
    }
    val->type = REAL32;
}

void to_r64(Value *val) {
    switch(val->type) {
        case INT32:  val->r64 = (double) val->i32; break;
        case INT64:  val->r64 = (double) val->i64; break;
        case BOOL:   val->r64 = (double) val->bl; break;
        case CHAR:   val->r64 = (double) val->chr; break;
        case REAL32: val->r64 = (double) val->r32; break;
        case REAL64: return;
        default:     return;
    }
    val->type = REAL64;
}

void to_chr(Value *val) {
    switch(val->type) {
        case INT32:  val->chr = (char) val->i32; break;
        case INT64:  val->chr = (char) val->i64; break;
        case BOOL:   val->chr = (char) val->bl; break;
        case CHAR:   return;
        case REAL32: val->chr = (char) val->r32; break;
        case REAL64: val->chr = (char) val->r64; break;
        default:     return;
    }
    val->type = CHAR;
}

void to_bl(Value *val) {
    switch(val->type) {
        case INT32:  val->bl = val->i32 != 0; break;
        case INT64:  val->bl = val->i64 != 0; break;
        case BOOL:   return;
        case CHAR:   val->bl = val->chr != 0; break;
        case REAL32: val->bl = val->r32 != 0; break;
        case REAL64: val->bl = val->r64 != 0; break;
        case NONE:   val->bl = false; break;
        case OBJ:    val->bl = true; break;
        default:     return;
    }
    val->type = BOOL;
}

ValueType resolve_type(Value* lhs, Value* rhs) {
    if (rhs->type == lhs->type) {
        return rhs->type;
    }
    ValueType final_type = max(rhs->type, lhs->type);
    Value* diff = final_type == rhs->type ? lhs : rhs;
    switch(final_type) {
        case INT32: to_i32(diff); break;
        case INT64: to_i64(diff); break;
        case REAL32: to_r32(diff); break;
        case REAL64: to_r64(diff); break;
        case CHAR: to_chr(diff); break;
        case BOOL: to_bl(diff); break;
        default: return 0;
    }
    return final_type;
}

bool add_overflow(Value* lhs, Value* rhs, ValueType type) {
    switch (type) {
        case INT32:     return (rhs->i32 >= 0) ? (lhs->i32 > INT32_MAX - rhs->i32) : (lhs->i32 < INT32_MIN - rhs->i32);
        case INT64:     return (rhs->i64 >= 0) ? (lhs->i64 > INT64_MAX - rhs->i64) : (lhs->i64 < INT64_MIN - rhs->i64);
        case REAL32:    return (rhs->r32 >= 0) ? (lhs->r32 > FLT_MAX - rhs->r32) : (lhs->r32 < -FLT_MAX - rhs->r32);
        case REAL64:    return (rhs->r64 >= 0) ? (lhs->r64 > DBL_MAX - rhs->r64) : (lhs->r64 < -DBL_MAX - rhs->r64);
        case CHAR:      return lhs->chr < rhs->chr;
        case BOOL:      return false;
        default:        return false;
    }
}

bool sub_overflow(Value* lhs, Value* rhs, ValueType type) {
    switch (type) {
        case INT32:     rhs->i32 = -rhs->i32; break;
        case INT64:     rhs->i64 = -rhs->i64; break;
        case REAL32:    rhs->r32 = -rhs->r32; break;
        case REAL64:    rhs->r64 = -rhs->r64; break;
        case CHAR:      return lhs->chr > UCHAR_MAX - rhs->chr; break;
        case BOOL:      return false;
        default:        return false;
    }
    return add_overflow(lhs, rhs, type);
}

//To repetetive, written by chat gpt
bool mul_overflow(Value* lhs, Value* rhs, ValueType type) {
    switch(type) {
        case INT32: {
            int32_t a = lhs->i32;
            int32_t b = rhs->i32;
            if (a == 0 || b == 0) return false;
            if (a == -1 && b == INT32_MIN) return true;
            if (b == -1 && a == INT32_MIN) return true;
            if (a > 0) {
                return (b > 0) ? (a > INT32_MAX / b)
                                : (b < INT32_MIN / a);
            } else { // a < 0
                return (b > 0) ? (a < INT32_MIN / b)
                                : (a < INT32_MAX / b);
            }
        }
        case INT64: {
            int64_t a = lhs->i64;
            int64_t b = rhs->i64;
            if (a == 0 || b == 0) return false;
            if (a == -1 && b == INT64_MIN) return true;
            if (b == -1 && a == INT64_MIN) return true;
            if (a > 0) {
                return (b > 0) ? (a > INT64_MAX / b)
                                : (b < INT64_MIN / a);
            } else { // a < 0
                return (b > 0) ? (a < INT64_MIN / b)
                                : (a < INT64_MAX / b);
            }
        }
        case REAL32: {
            float res = lhs->r32 * rhs->r32;
            return isinf(res);
        }
        case REAL64: {
            double res = lhs->r64 * rhs->r64;
            return isinf(res);
        }
        case CHAR: { // unsigned char
            unsigned char a = lhs->chr;
            unsigned char b = rhs->chr;
            return b != 0 && a > UCHAR_MAX / b;
        }
        case BOOL:
            return false; // logical OR cannot overflow
        default:
            return false;
    }
}

bool div_overflow(Value* lhs, Value* rhs, ValueType type) {
    switch(type) {
        case INT32: return lhs->i32 == INT32_MIN && rhs->i32 == -1;
        case INT64: return lhs->i64 == INT64_MIN && rhs->i64 == -1;
        case REAL32: { 
            float res = lhs->r32 / rhs->r32;
            return isinf(res); // overflow to infinity
        }
        case REAL64: {
            double res = lhs->r64 / rhs->r64;
            return isinf(res);
        }
        case CHAR: case BOOL: return false; // division cannot overflow
        default: return false;
    }
}
