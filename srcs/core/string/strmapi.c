#include "libcore.h"

/**
 * Description:
 * Allocates a new string and applies the function 'f' to each character
 * of 's', passing the character's index and value.
 *
 * Return:
 * The new string created from the successive applications of 'f',
 * or NULL if the initial memory allocation fails.
 */
char *strmapi(char const *s, char (*f)(unsigned int, char))
{
    unsigned int len;
    char *result;
    unsigned int i;

    if (!*s)
        return NULL;

    len = core_strlen(s);

    result = (char *)malloc(sizeof(char) * (len + 1));
    if (!result)
        return NULL;

    i = 0;
    while (i < len)
    {
        result[i] = f(i, s[i]);
        i++;
    }
    result[i] = '\0';

    return (result);
}
