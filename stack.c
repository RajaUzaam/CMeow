#include "vm.h"

void push_int(int32_t val) {
    stack = realloc(stack, (++stack_size) * sizeof(int32_t));
    if (sp >= (stack_size - 1)) {
        printf("Stack overflow!\n");
        exit(1);
    }
    stack[++sp] = val;
}

int32_t pop_int() {
    int32_t pop_val = stack[sp--];
    stack = realloc(stack, (--stack_size) * sizeof(int32_t));
    if (sp < -1) {
        printf("Stack underflow!\n");
        exit(1);
    }
    return pop_val;
}
