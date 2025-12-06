#include "includes.h"

/**
 * Description:
 * Allocates (with malloc(3)) and returns a string representing the
 * integer 'n'. The function handles negative numbers.
 *
 * Return:
 * The string representing the integer.
 * NULL if the allocation fails.
 */
static int get_len(int n)
{
    int len;

    if (n <= 0)
        len = 1;
    else
        len = 0;

    while (n != 0)
    {
        n /= 10;
        len++;
    }
    return (len);
}

char *itoa(int n)
{
    int len;
    char *result;
    long nb;

    nb = n;
    len = get_len(n);
    result = (char *)malloc(sizeof(char) * (len + 1));
    if (!result)
        return (NULL);

    *(result + len) = '\0';
    len--;

    if (nb == 0)
        *result = '0';

    if (nb < 0)
    {
        *result = '-';
        nb = -nb;
    }

    while (nb > 0)
    {
        *(result + len) = (nb % 10) + '0';
        nb /= 10;
        len--;
    }

    return (result);
}
