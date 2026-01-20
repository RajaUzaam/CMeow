#include "vm.h"

bool adjust_overflow(Value* lhs, Value* rhs, ValueType type, bool (of_func)(Value*, Value*, ValueType)) {
    if (of_mode == OF_PRMT) {
        return false;
    } else if (of_mode == OF_ERR) {
        last_of = of_func(lhs, rhs, type);
        return last_of;
    } else if (of_mode == OF_WRAP) {
        last_of = of_func(lhs, rhs, type);
        return false;
    }
    return true;
}
