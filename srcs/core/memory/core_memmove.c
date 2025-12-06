#include "includes.h"

/**
 * Description:
 * Copies n bytes from memory area src to memory area dest. The memory areas may overlap.
 *
 * Return:
 * A pointer to dest.
 */
void *core_memmove(void *dest, const void *src, size_t n)
{
    void *original_dest = dest;

    unsigned char *ptr_d = (unsigned char *)dest;
    const unsigned char *ptr_s = (const unsigned char *)src;

    if (n == 0)
        return (dest);

    if (ptr_d > ptr_s)
    {
        ptr_d += n;
        ptr_s += n;
        while (n-- > 0)
            *--ptr_d = *--ptr_s;
    }
    else
    {
        while (n-- > 0)
            *ptr_d++ = *ptr_s++;
    }
    return (original_dest);
}
