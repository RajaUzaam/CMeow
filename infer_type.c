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
    if (strlen == 3 && isascii(literal[1]) && literal[0] == '\'' && literal[2] == '\'') 
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
    else if (is_real(literal, str_len)) {return REAL;}
    else if (is_bl(literal, str_len))   {return BOOL;}
    else if (is_chr(literal, str_len))  {return CHAR;}
    else if (is_str(literal, str_len))  {return STR;}
    else {return -1;}
}