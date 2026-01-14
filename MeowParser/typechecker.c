#include "typechecker.h"

bool is_int(char** literal, uint64_t* curr, bool (*file_end)(void), char (*peek)(void), uint64_t* line) {
    while (isdigit(peek()) && !file_end()) {
        if (peek() == '\n')(*line)++;
        (*curr)++;
    }
    if (file_end()) return false;
    //(*curr)++;
    return true;
}

bool is_real(char* literal, uint64_t str_len) {
    bool dec = false;
    for (uint64_t i = 0; i < str_len; i++) {
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

bool is_chr(char* literal, uint64_t str_len) {
    if (str_len == 3 && isascii(literal[1]) && literal[0] == '\'' && literal[2] == '\'') 
        {return true;}
    return false;
}

bool is_bl(char* literal) {
    if (!strcmp(literal, "TRUE") || !strcmp(literal, "FALSE")) {return true;}
    return false;
}

bool is_str(char** literal, uint64_t* curr, uint64_t str_len, bool (*file_end)(void), char (*peek)(void), uint64_t* line) {
    while (peek() != '\"' && !file_end()) {
        if (peek() == '\n')(*line)++;
        (*curr)++;
    }
    if (file_end()) return false;
    (*curr)++;
    return true;
}