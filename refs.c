#include "assembler.h"

void create_unresolved_ref(char *name, int32_t addr, RefType type) {
    unresolved_refrences = realloc(unresolved_refrences, (++unresolved_refrences_size) * sizeof(Reference));
    unresolved_refrences[unresolved_refrences_size-1].name = _strdup(name);
    unresolved_refrences[unresolved_refrences_size-1].addr = addr;
    unresolved_refrences[unresolved_refrences_size-1].type = type;
}

void create_ref(char *name, int32_t addr, RefType type) {
    refrences = realloc(refrences, (++refrences_size) * sizeof(Reference));
    refrences[refrences_size-1].name = _strdup(name);
    refrences[refrences_size-1].addr = addr;
    refrences[refrences_size-1].type = type;
}

int32_t search_refs(char* name, RefType type, bool *found) {
    for (int32_t i = 0; i < refrences_size; i++) {
        //printf("|%s| |%d|\n", refrences[i].name, refrences[i].type);
        if (!strcmp(refrences[i].name, name) && (refrences[i].type == type)) {
            *found = true;
            return refrences[i].addr;
        }
    }
    *found = false;
    return -1;
}

void resolve_refs() {
    // printf("References:- \n");
    // for (int32_t i = 0; i < refrences_size; i++) {
    //     printf("{NAME} [%s] {ADDR} [0x%02X]\n", refrences[i].name, refrences[i].addr);
    // }
    // printf("Unresolved References:- \n");
    // for (int32_t i = 0; i < unresolved_refrences_size; i++) {
    //     printf("{NAME} [%s] {ADDR} [0x%02X]\n", unresolved_refrences[i].name, unresolved_refrences[i].addr);
    // }
    // printf("Resolving References:- \n");
    bool found;
    int32_t found_addr;
    int16_t relative_addr;
    for (int32_t i = 0; i < unresolved_refrences_size; i++) {
        //printf("Uresolved |%s|\n", unresolved_refrences[i].name);
        found_addr = search_refs(unresolved_refrences[i].name, unresolved_refrences[i].type, &found);
        if (found) {
            //printf("{%s} [0x%02X] [0x%02X]\n", unresolved_refrences[i].name, unresolved_refrences[i].addr, found_addr);
            if (unresolved_refrences[i].type == JMP_REF) {
                relative_addr = found_addr - (unresolved_refrences[i].addr-1);
            }
            else {
                relative_addr = found_addr;
            }
            //printf("{RELATIVE} [0x%02X]\n", relative_addr);
            memcpy(&_code[unresolved_refrences[i].addr], &relative_addr, sizeof(int16_t));
        } else {
            printf("Reference: \"%s\" not found!", unresolved_refrences[i].name);
            exit(1);
        }
    }
}
