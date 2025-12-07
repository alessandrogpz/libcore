#include "libcore.h"

/**
 * Description:
 * Converts the initial portion of the string pointed to by str to int representation.
 *
 * Return:
 * The converted value.
 */
int core_atoi(const char *n)
{
    int sign = 1;
    int result = 0;

    while (*n == ' ' || (*n >= '\t' && *n <= '\r'))
        n++;

    if (*n == '-' || *n == '+')
    {
        if (*n == '-')
            sign = -1;
        n++;
    }

    while (*n >= '0' && *n <= '9')
    {
        result = result * 10 + (*n - '0');
        n++;
    }
    return (result * sign);
}
