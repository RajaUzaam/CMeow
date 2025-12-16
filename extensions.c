#include "assembler.h"

uint64_t make_extension(uint64_t val) {
    uint64_t extension_needed = 0;
    if (val <= UINT8_MAX)        {extension_needed = 0;} 
    else if (val <= UINT16_MAX)  {extension_needed = 1;} 
    else if (val <= UINT32_MAX)  {extension_needed = 3;} 
    else if (val <= UINT64_MAX)  {extension_needed = 7;}
    return extension_needed;
}