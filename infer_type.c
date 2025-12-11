#include "infer_type.h"
#include "instruction_set.h"

bool is_int(char* literal, int32_t str_len) {
    for (int32_t i = 0; i < str_len; i++) {
        if (!isdigit(literal[i])) {return false;}
    }
    return true;
}

bool is_real(char* literal, int32_t str_len) {
    bool dec = false;
    for (int32_t i = 0; i < str_len; i++) {
        if (!isdigit(literal[i])) {
            if (literal[i] != '.') {return false;}
            else {
                if (dec) {return false;}
                dec = true;
            }
        }
    }
    return dec;
}

bool is_chr(char* literal, int32_t str_len) {
    if (strlen(literal) == 3 && isascii(literal[1]) && literal[0] == '\'' && literal[2] == '\'') 
        {return true;}
    return false;
}

bool is_bl(char* literal, int32_t str_len) {
    if (str_len == 1 && (literal[0] == '1' || literal[0] == '0'))
        {return true;}
    return false;
}

bool is_str(char* literal, int32_t str_len) {
    if (literal[0] != '"' || literal[str_len-1]) {return false;}
    for (int32_t i = 1; i < (str_len-1); i++) {
        if (!isascii(literal[i])) {
            return false;
        }
    }
    return true;
}

int8_t check_type(char* literal) {
    int32_t str_len = strlen(literal);
    if      (is_int(literal, str_len))  {return INT32;}
    else if (is_real(literal, str_len)) {return REAL32;}
    else if (is_bl(literal, str_len))   {return BOOL;}
    else if (is_chr(literal, str_len))  {return CHAR;}
    else if (is_str(literal, str_len))  {return STR;}
    else {return -1;}
}

void fill_value(char* literal, Value* val, bool dynamic) {
    switch (check_type(literal)) {
        case INT32: {
            (*val).type = INT32;
            (*val).dynamic = dynamic;
            (*val).value.i32 = atoi(literal);
            break;
        }
        default: {
            perror("BREAK!");
            exit(1);
        }
    }
    return;
}

bool make_value(char* literal, Value* val, bool dynamic, ValueType type) {
    int8_t known_type = check_type(literal);
    (*val).dynamic = false;
    (*val).type = type;
    if (type == DYNAMIC) {
        (*val).dynamic = true;
        (*val).type = known_type;
        type = known_type;
    }

    if (known_type >= 0) {
        if (TypeInt(known_type) == TypeInt(type)) {
            switch(type) {
                case BOOL: (*val).value.i32 = (bool) atoi(literal); break;
                case CHAR: (*val).value.i32 = (char) literal[1]; break;
                case INT32: (*val).value.i32 = (int32_t) atoi(literal); break;
                case INT64: (*val).value.i32 = (int64_t) atol(literal); break;
                default: exit(1);
            }
        }
        else if (TypeReal(known_type) == TypeReal(type)) {
            switch(type) {
                case REAL32: (*val).value.r32 = (float) atof(literal); break;
                case REAL64: (*val).value.r64 = (double) atof(literal); break;
                default: exit(1);
            }
        }
    } else {
        return false;
    }
    return true;
}

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
        case INT32:
            val->value.i32 = (int32_t) to_int64(val); break;
        case INT64:
            val->value.i64 = to_int64(val); break;
        case REAL32:
            val->value.r32 = (float) to_double(val); break;
        case REAL64:
            val->value.r64 = to_double(val); break;
        case BOOL:
            val->value.bl = to_int64(val) != 0; break;
        case CHAR:
            val->value.chr = (char) to_int64(val); break;
        default:
            printf("what the hell are you feeding me!\n");
            exit(1);
    }

    val->type = target;
}

void promote(Value *val, ValueType *target_type) {
    if (IsInt(*target_type)) {to_int64(val);}
    else if (IsReal(*target_type)) {to_double(val);}
}