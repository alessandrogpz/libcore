#include "libcore.h"

/**
 * Description:
 * Scans the initial n bytes of the memory area pointed to by s for the first instance of c.
 *
 * Return:
 * A pointer to the matching byte or NULL if the character does not occur in the given memory area.
 */
void *core_memchr(const void *s, int c, size_t n)
{
    const unsigned char *ptr = s;

    while (n-- > 0)
    {
        if (*ptr == (unsigned char)c)
            return ((void *)ptr);
        ptr++;
    }
    return (NULL);
}
