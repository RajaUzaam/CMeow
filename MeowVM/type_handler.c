#include "type_handler.h"

// Convert any Value to int64_t (truncates floats)
int64_t to_int64(const Value *val) {
    switch(val->type) {
        case INT32:  return val->value.i32;
        case INT64:  return val->value.i64;
        case BOOL:   return val->value.bl ? 1 : 0;
        case CHAR:   return val->value.chr;
        case REAL32: return (int64_t) val->value.r32;
        case REAL64: return (int64_t) val->value.r64;
        default:     return 0; // PTR or unsupported
    }
}

// Convert any Value to double (for floating-point casts)
double to_double(const Value *val) {
    switch(val->type) {
        case INT32:  return (double) val->value.i32;
        case INT64:  return (double) val->value.i64;
        case BOOL:   return (double) val->value.bl ? 1.0 : 0.0;
        case CHAR:   return (double) val->value.chr;
        case REAL32: return val->value.r32;
        case REAL64: return val->value.r64;
        default:     return 0.0;
    }
}

void to_i32(Value *val) {
    switch(val->type) {
        case INT32:  return;
        case INT64:  val->value.i32 = (int32_t) val->value.i64; break;
        case BOOL:   val->value.i32 = (int32_t) val->value.bl; break;
        case CHAR:   val->value.i32 = (int32_t) val->value.chr; break;
        case REAL32: val->value.i32 = (int32_t) val->value.r32; break;
        case REAL64: val->value.i32 = (int32_t) val->value.r64; break;
        default:     return;
    }
    val->type = INT32;
}

void to_i64(Value *val) {
    switch(val->type) {
        case INT32:  val->value.i64 = (int64_t) val->value.i32; break;
        case INT64:  return;
        case BOOL:   val->value.i64 = (int64_t) val->value.bl; break;
        case CHAR:   val->value.i64 = (int64_t) val->value.chr; break;
        case REAL32: val->value.i64 = (int64_t) val->value.r32; break;
        case REAL64: val->value.i64 = (int64_t) val->value.r64; break;
        default:     return;
    }
    val->type = INT64;
}

void to_r32(Value *val) {
    switch(val->type) {
        case INT32:  val->value.r32 = (float) val->value.i32; break;
        case INT64:  val->value.r32 = (float) val->value.i64; break;
        case BOOL:   val->value.r32 = (float) val->value.bl; break;
        case CHAR:   val->value.r32 = (float) val->value.chr; break;
        case REAL32: return;
        case REAL64: val->value.r32 = (float) val->value.r64; break;
        default:     return;
    }
    val->type = REAL32;
}

void to_r64(Value *val) {
    switch(val->type) {
        case INT32:  val->value.r64 = (double) val->value.i32; break;
        case INT64:  val->value.r64 = (double) val->value.i64; break;
        case BOOL:   val->value.r64 = (double) val->value.bl; break;
        case CHAR:   val->value.r64 = (double) val->value.chr; break;
        case REAL32: val->value.r64 = (double) val->value.r32; break;
        case REAL64: return;
        default:     return;
    }
    val->type = REAL64;
}

void to_chr(Value *val) {
    switch(val->type) {
        case INT32:  val->value.chr = (char) val->value.i32; break;
        case INT64:  val->value.chr = (char) val->value.i64; break;
        case BOOL:   val->value.chr = (char) val->value.bl; break;
        case CHAR:   return;
        case REAL32: val->value.chr = (char) val->value.r32; break;
        case REAL64: val->value.chr = (char) val->value.r64; break;
        default:     return;
    }
    val->type = CHAR;
}

void to_bl(Value *val) {
    switch(val->type) {
        case INT32:  val->value.bl = (bool) val->value.i32; break;
        case INT64:  val->value.bl = (bool) val->value.i64; break;
        case BOOL:   return;
        case CHAR:   val->value.bl = (bool) val->value.chr; break;
        case REAL32: val->value.bl = (bool) val->value.r32; break;
        case REAL64: val->value.bl = (bool) val->value.r64; break;
        default:     return;
    }
    val->type = BOOL;
}

ValueType resolve_type(Value* lhs, Value* rhs) {
    if (rhs->type == lhs->type) {
        return rhs->type;
    }
    ValueType final_type = max(rhs->type, lhs->type);
    Value* diff = final_type == rhs->type ? rhs : lhs;
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

// Cast val to target type
void cast_type(Value *val, ValueType target) {
    if(val->type == target) return;

    switch(target) {
        case BOOL:
            val->value.bl = (uint8_t) to_int64(val); break;
        case CHAR:
            val->value.chr = (uint8_t) to_int64(val); break;
        case INT32:
            val->value.i32 = (int32_t) to_int64(val); break;
        case INT64:
            val->value.i64 = to_int64(val); break;
        case REAL32:
            val->value.r32 = (float) to_double(val); break;
        case REAL64:
            val->value.r64 = to_double(val); break;
        default:
            printf("what the hell are you feeding me!\n");
            exit(1);
    }

    val->type = target;
}



void promote(Value *val, ValueType *target_type) {
    if (TypeInt(*target_type)) {
        val->value.i64 = to_int64(val);
        val->type = INT64;
    }
    else if (TypeReal(*target_type)) {
        val->value.r64 = to_double(val);
        val->type = REAL64;
    }
}