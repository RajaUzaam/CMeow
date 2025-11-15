#include "vm.h"

void push_int(Value val) {
    vm.stack = realloc(vm.stack, (++vm.sp) * sizeof(Value));
    // if (sp >= (stack_size - 1)) {
    //     printf("Stack overflow!\n");
    //     exit(1);
    // }
    printf("REALLOCED: %d\n", vm.sp);
    vm.stack[vm.sp] = val;
}

Value pop_int() {
    if (vm.sp < 0) {
        printf("Stack underflow!\n");
        exit(1);
    }

    Value pop_val = vm.stack[vm.sp--];
    printf("POP VAL: %d | SP: %d\n", pop_val.value.int_val, vm.sp);

    return pop_val;
}
