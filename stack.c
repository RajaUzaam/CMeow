#include "vm.h"

void push_int(Value val) {
    vm.stack = realloc(vm.stack, (++vm.sp + 1) * sizeof(Value));
    vm.stack[vm.sp] = val;
}

Value pop_int() {
    if (vm.sp < 0) {
        printf("Stack underflow!\n");
        exit(1);
    }

    Value pop_val = vm.stack[vm.sp--];

    return pop_val;
}
