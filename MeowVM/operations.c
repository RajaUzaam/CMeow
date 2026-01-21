#include "operations.h"

bool adjust_overflow(Value* lhs, Value* rhs, ValueType type, bool (of_func)(Value*, Value*, ValueType)) {
    if (vm.flags.of_mode == OF_PRMT) {
        return false;
    } else if (vm.flags.of_mode == OF_ERR) {
        bool last_of = of_func(lhs, rhs, type);
        return last_of;
    } else if (vm.flags.of_mode == OF_WRAP) {
        bool last_of = of_func(lhs, rhs, type);
        return false;
    }
    return true;
}
