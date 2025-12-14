#include "assembler.h"

void create_unresolved_ref(char *name, uint64_t func_addr, uint64_t addr, RefType type) {
    unresolved_refrences = realloc(unresolved_refrences, (++unresolved_refrences_size) * sizeof(Reference));
    unresolved_refrences[unresolved_refrences_size-1].name = _strdup(name);
    unresolved_refrences[unresolved_refrences_size-1].func_idx = func_addr;
    unresolved_refrences[unresolved_refrences_size-1].addr = addr;
    unresolved_refrences[unresolved_refrences_size-1].type = type;
}

void create_ref(char *name, uint64_t func_addr, uint64_t addr, RefType type) {
    refrences = realloc(refrences, (++refrences_size) * sizeof(Reference));
    refrences[refrences_size-1].name = _strdup(name);
    refrences[refrences_size-1].addr = addr;
    refrences[refrences_size-1].func_idx = func_addr;
    refrences[refrences_size-1].type = type;
}

uint64_t search_refs(char* name, RefType type, bool *found) {
    for (uint64_t i = 0; i < refrences_size; i++) {
        if (!strcmp(refrences[i].name, name) && (refrences[i].type == type)) {
            *found = true;
            return i;
        }
    }
    *found = false;
    return -1;
}

void resolve_refs() {
    // for (int32_t i = 0; i < refrences_size; i++) {
    //     printf("Name: %s | FuncAddr: %d | CodeAddr: %d | Type: %d\n", refrences[i].name, refrences[i].func_idx, refrences[i].addr, refrences[i].type);
    // }
    // printf("======\n");
    // for (int32_t i = 0; i < unresolved_refrences_size; i++) {
    //     printf("Name: %s | FuncAddr: %d | CodeAddr: %d | Type: %d\n", unresolved_refrences[i].name, unresolved_refrences[i].func_idx, unresolved_refrences[i].addr, unresolved_refrences[i].type);
    // }
    bool found;
    uint64_t found_addr;
    int64_t relative_addr;
    for (uint64_t i = 0; i < unresolved_refrences_size; i++) {
        found_addr = search_refs(unresolved_refrences[i].name, unresolved_refrences[i].type, &found);
        if (found) {
            if (unresolved_refrences[i].type == JMP_REF) {
                relative_addr = refrences[found_addr].addr - (unresolved_refrences[i].addr-1);
                memcpy(&_functions[unresolved_refrences[i].func_idx].code[unresolved_refrences[i].addr], &relative_addr, sizeof(int16_t));
            }
            else if (unresolved_refrences[i].type == FUNC_REF) {
                relative_addr = refrences[found_addr].func_idx;
                memcpy(&_functions[unresolved_refrences[i].func_idx].code[unresolved_refrences[i].addr], &relative_addr, sizeof(int16_t));
            }
            else {
                printf("unknown ref typen\n"); exit(1);
            }
        } else {
            printf("Reference: \"%s\" not found!", unresolved_refrences[i].name);
            exit(1);
        }
    }
}
