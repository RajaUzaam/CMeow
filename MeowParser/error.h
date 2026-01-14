#ifndef ERROR
#define ERROR

#include "header.h"

enum {
    CUSTOM_ERROR,
    SYNTAX_ERROR,
};

#endif

void Error(bool* err_status, uint64_t line_loc, uint64_t statement_loc, uint8_t error_code, char* error_msg);
void SimpleError(bool* err_status, char* msg, uint64_t line_loc);
