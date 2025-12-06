#include "includes.h"

/**
 * Description:
 * Compares the first n bytes (each interpreted as unsigned char) of the memory areas s1 and s2.
 *
 * Return:
 * An integer less than, equal to, or greater than zero if the first n bytes of s1 is found, respectively, to be less than, to match, or be greater than the first n bytes of s2.
 */
int core_memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char *p1 = s1;
    const unsigned char *p2 = s2;

    while (n-- > 0)
    {
        if (*p1 != *p2)
            return (*p1 - *p2);
        p1++;
        p2++;
    }

    return (0);
}
