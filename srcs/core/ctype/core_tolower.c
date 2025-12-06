#include "includes.h"

/**
 * Description:
 * Converts a strictly uppercase letter to its lowercase equivalent.
 *
 * Return:
 * The value of the converted letter, or c if the conversion was not possible.
 */
int core_tolower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return (c - 'A' + 'a');
    return (c);
}
