#include "includes.h"

/**
 * Description:
 * Applies the function 'f' to each character of the string 's',
 * passing its index as the first argument. Each character is passed by
 * address (pointer) to 'f' so the original string 's' can be modified
 * in place if necessary.
 *
 * Return:
 * None (void).
 */
void striteri(char *s, void (*f)(unsigned int, char *))
{
    char *current_s;
    unsigned int i;

    if (!s)
        return;

    current_s = s;
    i = 0;

    while (*current_s)
    {
        f(i, current_s);
        current_s++;
        i++;
    }
}