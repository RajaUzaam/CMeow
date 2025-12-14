#include "assembler.h"

uint64_t make_extension(uint64_t func_idx, uint64_t addr, uint64_t val) {
    uint64_t extension_needed = 0;
    if (val < UINT8_MAX)        {extension_needed = 0;} 
    else if (val < UINT16_MAX)  {extension_needed = 1;} 
    else if (val < UINT32_MAX)  {extension_needed = 3;} 
    else if (val < UINT64_MAX)  {extension_needed = 7;}
    if (extension_needed > 0) {
        extensions[func_idx]->extensions = realloc( extensions[func_idx]->extensions, sizeof(ExtendOper) * (++(extensions[func_idx]->extensions_size)) );
        extensions[func_idx]->extensions[extensions[func_idx]->extensions_size - 1].addr = addr;
        extensions[func_idx]->extensions[extensions[func_idx]->extensions_size - 1].type = extension_needed+(ESIZE1-1);
    } 
    return extension_needed;
}