#include "includes.h"

/**
 * Description:
 * Copies n bytes from memory area src to memory area dest. The memory areas must not overlap.
 *
 * Return:
 * A pointer to dest.
 */
void *core_memcpy(void *dest, const void *src, size_t n)
{
    void *original_dest = dest;

    unsigned char *ptr_d = (unsigned char *)dest;
    const unsigned char *ptr_s = (const unsigned char *)src;

    while (n-- > 0)
        *ptr_d++ = *ptr_s++;

    return (original_dest);
}
