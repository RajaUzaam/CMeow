#include "rt_error.h"

void throw_err(ErrObj err_obj) {
    printf("At Line: %d | ", err_obj.line);
    printf("%s\n", err_obj.msg);
    exit(err_obj.code);
}

// void raise_err(ERR_CODE err_code) {
    
// }
