#include "libcore.h"

/**
 * Description:
 * Converts a strictly lowercase letter to its uppercase equivalent.
 *
 * Return:
 * The value of the converted letter, or c if the conversion was not possible.
 */
int core_toupper(int c)
{
    if (c >= 'a' && c <= 'z')
        return (c - 'a' + 'A');
    return (c);
}
