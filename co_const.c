#include "vm.h"

int16_t search_const(int32_t val) {
    for (int32_t i = 0; i < co_consts_size; i++) {
        if (co_consts[i].value.int_val == val) {
            return i;
        }
    }

    return -1;
}

// void add_const(int32_t val) {
//     if (search_const(val) == -1) {
//         co_consts = realloc(co_consts, ++co_consts_size);
//         co_consts[co_consts_size-1] = val;
//     }
// }
