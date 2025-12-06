#include "includes.h"

/**
 * Description:
 * Fills the first n bytes of the memory area pointed to by s with the constant byte c.
 *
 * Return:
 * A pointer to the memory area s.
 */
void *core_memset(void *s, int c, size_t n)
{
    unsigned char *ptr = s;

    while (n > 0)
    {
        *ptr = (unsigned char)c;
        ptr++;
        n--;
    }
    return (s);
}
