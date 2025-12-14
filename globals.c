#include "vm.h"

void store_globals(uint64_t addr, Value val) {
    if (addr >= globals_size) {
        globals_size = addr;
        globals = realloc(globals, (++globals_size) * sizeof(Value));
    }
    globals[addr] = val;
}

Value get_globals(uint64_t addr) {
    if (addr >= globals_size) {
        printf("Memory Address Undefined!");
        exit(1);
    }
    return globals[addr];
}
