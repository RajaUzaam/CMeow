#include "vm.h"

void store_globals(int16_t addr, Value val) {
    if (addr >= globals_size) {
        globals_size = addr;
        globals = realloc(globals, (++globals_size) * sizeof(int32_t));
    }
    globals[addr] = val;
}

Value get_globals(int16_t addr) {
    if (addr >= globals_size) {
        printf("Memory Address Undefined!");
        exit(1);
    }
    return globals[addr];
}
