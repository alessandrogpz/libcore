#include "includes.h"

/**
 * Description:
 * Returns a pointer to the last occurrence of the character c in the string s.
 *
 * Return:
 * A pointer to the matched character or NULL if the character is not found.
 */
char *core_strrchr(const char *s, int c)
{
    char *candidate;

    candidate = NULL;
    while (*s)
    {
        if (*s == (char)c)
            candidate = (char *)s;
        s++;
    }

    if (*s == (char)c)
        return ((char *)s);

    return (candidate);
}
