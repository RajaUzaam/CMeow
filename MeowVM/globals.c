#include "globals.h"

void store_globals(uint64_t addr, Value val) {
    if (addr >= vm.globals_size) {
        vm.globals_size = addr;
        vm.globals = realloc(vm.globals, (++vm.globals_size) * sizeof(Value));
        if (!vm.globals) {
            printf("Globals Reallocation Failed!\n"); exit(1);
        }
    }
    vm.globals[addr] = val;
}

Value get_globals(uint64_t addr) {
    if (addr >= vm.globals_size) {
        printf("Memory Address Undefined!");
        exit(1);
    }
    return vm.globals[addr];
}
