#include "libcore.h"

/**
 * Description:
 * Returns a pointer to the first occurrence of the character c in the string s.
 *
 * Return:
 * A pointer to the matched character or NULL if the character is not found.
 */
char *core_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }

    if (*s == (char)c)
        return ((char *)s);

    return (NULL);
}
