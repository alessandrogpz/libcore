#include "libcore.h"

/**
 * Description:
 * Copies up to dstsize - 1 characters from the string src to dst, NUL-terminating the result if dstsize is not 0.
 *
 * Return:
 * The total length of the string they tried to create.
 */
size_t core_strlcpy(char *dst, const char *src, size_t dsize)
{
    size_t src_len = core_strlen(src);

    if (dsize == 0)
        return (src_len);

    while (dsize-- > 1 && *src)
        *dst++ = *src++;
    *dst = '\0';

    return (src_len);
}
