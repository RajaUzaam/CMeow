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
        case BOOL:   return val->value.bl ? 1.0 : 0.0;
        case CHAR:   return (double) val->value.chr;
        case REAL32: return (double) val->value.r32;
        case REAL64: return val->value.r64;
        default:     return 0.0;
    }
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