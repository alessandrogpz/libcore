#include "libcore.h"

/**
 * Description:
 * Allocates (with malloc(3)) and returns a substring from the string 's'.
 * The substring begins at index 'start' and is of maximum size 'len'.
 *
 * Return:
 * The substring. NULL if the allocation fails.
 */
char *substr(char const *s, unsigned int start, size_t len)
{
    size_t s_len;
    size_t copy_len;
    char *sub;

    if (!s)
        return (NULL);

    s_len = core_strlen(s);

    // 1. Calculate actual length to copy
    if (start >= s_len)
        copy_len = 0; // Start is past end of string -> Empty string
    else if (len > s_len - start)
        copy_len = s_len - start; // Requested len is too long -> Truncate
    else
        copy_len = len; // Fits perfectly

    // 2. Allocate exactly what we need
    sub = (char *)malloc(sizeof(char) * (copy_len + 1));
    if (!sub)
        return (NULL);

    // 3. Copy and null-terminate
    if (copy_len > 0)
        core_memmove(sub, s + start, copy_len);
    sub[copy_len] = '\0';

    return (sub);
}