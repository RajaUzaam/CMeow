#ifndef TYPECHECKER
#define TYPECHECKER

#include "header.h"

#endif

bool is_int(char** literal, uint64_t* curr, bool (*file_end)(void), char (*peek)(void), uint64_t* line);
bool is_str(char** literal, uint64_t* curr, uint64_t str_len, bool (*file_end)(void), char (*peek)(void), uint64_t* line);