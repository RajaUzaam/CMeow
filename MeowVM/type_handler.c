#include "type_handler.h"

// const char type_suffix[PRIMITIVES][MAX_TYPE_SUF] = {
//     "sep", "bl", "ch", "i32", "i64", "r32", "r64"
// };

// void analyze_literal(char* literal, char** data, char** suffix) {
//     *data = NULL;
//     *suffix = NULL;
//     uint64_t data_len = 0, suffix_len = 0, i = 0;
//     uint64_t str_len = strlen(literal);
//     char c;
//     while ((c = literal[i]) && ((c >= '0' && c <= '9') || c == '.')) {
//         *data = realloc(*data, sizeof(char)*(++data_len));
//         (*data)[data_len-1] = c;
//         i++;
//     }
//     if (*data == NULL) {return;}
//     *data = realloc(*data, sizeof(char)*(++data_len));
//     (*data)[data_len-1] = '\0';
//     if (i == str_len) {return;}
//     while ((c = literal[i]) && (c != '\0')) {
//         *suffix = realloc(*suffix, sizeof(char)*(++suffix_len));
//         (*suffix)[suffix_len-1] = c;
//         i++;
//     }
//     *suffix = realloc(*suffix, sizeof(char)*(++suffix_len));
//     (*suffix)[suffix_len-1] = '\0';
//     return;
// }

// bool is_int(char* literal, uint64_t str_len) {
//     for (uint64_t i = 0; i < str_len; i++) {
//         if (!isdigit(literal[i])) {
//             return false;
//         }
//     }
//     return true;
// }

// bool is_real(char* literal, uint64_t str_len) {
//     bool dec = false;
//     for (uint64_t i = 0; i < str_len; i++) {
//         if (!isdigit(literal[i])) {
//             if (literal[i] != '.') {return false;}
//             else {
//                 if (dec) {return false;}
//                 dec = true;
//             }
//         }
//     }
//     return dec;
// }

// bool is_chr(char* literal, uint64_t str_len) {
//     if (str_len == 3 && isascii(literal[1]) && literal[0] == '\'' && literal[2] == '\'') 
//         {return true;}
//     return false;
// }

// bool is_bl(char* literal) {
//     if (!strcmp(literal, "TRUE") || !strcmp(literal, "FALSE")) {return true;}
//     return false;
// }

// bool is_str(char* literal, int32_t str_len) {
//     if (literal[0] != '"' || literal[str_len-1]) {return false;}
//     for (int32_t i = 1; i < (str_len-1); i++) {
//         if (!isascii(literal[i])) {
//             return false;
//         }
//     }
//     return true;
// }

// bool valid_num(char* literal, bool *dec) {
//     uint64_t len = (uint64_t) strlen(literal);
//     for (uint64_t i = 0; i < len; i++) {
//         if (!isdigit(literal[i])) {
//             if (literal[i] != '.') {return false;}
//             else {
//                 if (*dec) {return false;}
//                 *dec = true;
//             }
//         }
//     }
//     return true;
// }

// TypeRepresentation check_type(char* literal) {
//     char* data = NULL;
//     char* suffix = NULL;
//     analyze_literal(literal, &data, &suffix);
//     uint64_t str_len = strlen(literal);
//     TypeRepresentation res;
//     res.data = NULL; res.suffixed = false; res.type = -1;
//     res.data = literal;
//     if (suffix != NULL) {
//         bool dec = false;
//         if (valid_num(data, &dec)) {
//             res.suffixed = true;
//             res.data = data;
//             if (!strcmp(suffix, type_suffix[INT32])) {
//                 if (dec) {printf("%s%s is Invalid!\n", res.data, type_suffix[INT32]); exit(1);}
//                 res.type = INT32;
//             }
//             else if (!strcmp(suffix, type_suffix[INT64]) || !strcmp(suffix, "i")) {
//                 if (dec) {printf("%s%s is Invalid!\n", res.data, type_suffix[INT64]); exit(1);}
//                 res.type = INT64;
//             }
//             else if (!strcmp(suffix, type_suffix[CHAR])) {
//                 if (atoi(res.data) < 0 || atoi(res.data) > 255) {printf("Invalid Bool!\n"); exit(1);}
//                 res.type = CHAR;
//             }
//             else if (!strcmp(suffix, type_suffix[BOOL])) {
//                 if (atoi(res.data) < 0 || atoi(res.data) > 1) {printf("Invalid Bool!\n"); exit(1);}
//                 res.type = BOOL;
//             }
//             else if (!strcmp(suffix, type_suffix[REAL32])) {res.type = REAL32;}
//             else if (!strcmp(suffix, type_suffix[REAL64]) || !strcmp(suffix, "r")) {res.type = REAL64;}
//             else {
//                 printf("Unknown Suffix!\n"); exit(1);
//             }
//         } else {
//             printf("Unknown Type!\n"); exit(1);
//         }
//     }
//     else if (data == NULL) {
//         if (is_chr(literal, str_len)) {res.type = CHAR;}
//         else if (is_bl(literal)) {res.type = BOOL;}
//         else {
//             printf("Unknown Type!!\n"); exit(1);
//         }
//     } 
//     else {
//         if (is_int(literal, str_len)) {
//             int64_t num = atol(literal);
//             if (num > INT32_MAX || num < INT32_MIN) {res.type = INT64;}
//             res.type = INT32;
//         }
//         else if (is_real(literal, str_len)) {
//             double num = atof(literal);
//             if (num > FLT_MAX && num < FLT_MIN) {res.type = REAL64;}
//             res.type = REAL32;
//         }
//         else {
//             printf("Unknown Type!!!\n"); exit(1);
//         }
//     }
//     return res;
// }

// bool make_value(char* literal, Value* val, bool dynamic, int8_t type) {
//     TypeRepresentation rep = check_type(literal);
//     int8_t known_type = rep.type;
//     (*val).dynamic = false;
//     (*val).type = type;
//     // if (type == DYNAMIC) {
//     //     (*val).dynamic = true;
//     //     (*val).type = known_type;
//     //     type = known_type;
//     // } 
//     if (type == -1) {
//         type = known_type;
//         (*val).type = type;
//     }
//     if (known_type >= 0) {
//         if (TypeInt(known_type) && TypeInt(type)) {
//             switch(type) {
//                 case BOOL:
//                     if (rep.suffixed) {(*val).value.bl = (uint8_t) atoi(rep.data);}
//                     else {(*val).value.bl = (uint8_t) !strcmp(rep.data, "TRUE") ? 1 : 0;}
//                 break;
//                 case CHAR:
//                     if (rep.suffixed) {(*val).value.chr = (uint8_t) atoi(rep.data);}
//                     else {(*val).value.chr = (uint8_t) rep.data[1];}
//                 break;
//                 case INT32: (*val).value.i32 = (int32_t) atoi(rep.data); break;
//                 case INT64: (*val).value.i64 = (int64_t) atol(rep.data); break;
//                 default: exit(1);
//             }
//         }
//         else if (TypeReal(known_type) && TypeReal(type)) {
//             switch(type) {
//                 case REAL32: (*val).value.r32 = (float) atof(rep.data); break;
//                 case REAL64: (*val).value.r64 = (double) atof(rep.data); break;
//                 default: exit(1);
//             }
//         } else {
//             printf("Wait what?"); 
//             exit(1);
//         }
//     } else {
//         printf("Not a known Value!\n");
//         return false;
//     }
//     return true;
// }

// bool make_const(char* literal, Value* val, void (*const_add)(Value)) {
//     bool to_add = false;
//     if (literal[0] == '#') {
//         literal += 1;
//         to_add = true;
//     }
//     if (make_value(literal, val, false, -1)) {
//         if (to_add) {
//             const_add(*val);
//         }
//         return true;
//     }
//     return false;
// }

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