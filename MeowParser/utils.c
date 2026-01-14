#include "utils.h"

char *sub_str(char **str, size_t start, size_t len, size_t slen)
{
    if (!(*str))
        return NULL;

    if (start > slen || start + len > slen)
        return NULL;

    char *out = malloc(len + 1);
    if (!out)
        return NULL;

    memcpy(out, (*str) + start, len);
    out[len] = '\0';

    return out;
}