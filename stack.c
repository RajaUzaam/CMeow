#include "vm.h"

void push_val(Value val) {
    vm.stack = realloc(vm.stack, (++vm.sp + 1) * sizeof(Value));
    if (!vm.stack) {
        printf("Stack overflow!\n");
        exit(1);
    }
    vm.stack[vm.sp] = val;
}

Value pop_val() {
    if (vm.sp < 0) {
        printf("Stack underflow!\n");
        exit(1);
    }

    Value pop_val = vm.stack[vm.sp--];

    return pop_val;
}
