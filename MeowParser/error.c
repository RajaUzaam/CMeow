#include "error.h"

static void Report(uint64_t line_loc, uint64_t statement_loc, uint8_t error_code, char* error_msg) {
    if (error_code == SYNTAX_ERROR) {
        printf("At line %lld | Error: Unexpected \"%s\" at %lld\n", line_loc, error_msg, statement_loc);
    } else {
        printf("Line: | %s\n", error_msg);
    }
}
void Error(bool* err_status, uint64_t line_loc, uint64_t statement_loc, uint8_t error_code, char* error_msg) {
    Report(line_loc, statement_loc, error_code, error_msg);
    *err_status = true;
}
void SimpleError(bool* err_status, char* msg, uint64_t line_loc) {
    Report(line_loc, 0, -1, msg);
    *err_status = true;
}