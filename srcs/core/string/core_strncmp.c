#include "includes.h"

/**
 * Description:
 * Compares the two strings s1 and s2. It compares not more than n characters.
 *
 * Return:
 * An integer less than, equal to, or greater than zero if s1 (or the first n bytes thereof) is found, respectively, to be less than, to match, or be greater than s2.
 */
int core_strncmp(const char *s1, const char *s2, size_t n)
{
    while (n-- > 0)
    {
        if (*s1 != *s2 || *s1 == '\0')
            return ((unsigned char)*s1 - (unsigned char)*s2);
        s1++;
        s2++;
    }

    return (0);
}
