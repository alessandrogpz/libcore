#include "includes.h"

/**
 * Description:
 * Appends the string 'src' to the end of 'dst'. It will append at most
 * 'dsize' - strlen(dst) - 1 bytes, null-terminating the result.
 *
 * Return:
 * The total length of the string it tried to create (initial length of 'dst'
 * plus length of 'src').
 */
size_t core_strlcat(char *dst, const char *src, size_t dsize)
{
    size_t src_len = core_strlen(src);
    size_t dst_len = 0;

    while (dst_len < dsize && dst[dst_len])
        dst_len++;

    if (dst_len == dsize)
        return (dsize + src_len);

    size_t copy_limit = dsize - dst_len;

    dst += dst_len;

    while (copy_limit-- > 1 && *src)
        *dst++ = *src++;
    *dst = '\0';

    return (dst_len + src_len);
}
