#include "libcore.h"

/**
 * Description:
 * Returns a pointer to a new string which is a duplicate of the string s.
 *
 * Return:
 * A pointer to the duplicated string, or NULL if insufficient memory was available.
 */
char *core_strdup(const char *s)
{
    size_t len;
    char *dup;

    len = core_strlen(s);

    dup = (char *)malloc(len + 1);
    if (!dup)
        return NULL;

    core_memcpy(dup, s, len);

    dup[len] = '\0';

    return dup;
}
