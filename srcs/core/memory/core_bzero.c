#include "libcore.h"

/**
 * Description:
 * Erases the data in the n bytes of the memory starting at the location pointed to by s, by writing zeros (bytes containing '\0') to that area.
 *
 * Return:
 * None.
 */
void core_bzero(void *s, size_t n)
{
    unsigned char *ptr = s;

    while (n-- > 0)
        *ptr++ = '\0';
}
