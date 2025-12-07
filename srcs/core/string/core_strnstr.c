#include "libcore.h"

/**
 * Description:
 * Locates the first occurrence of the null-terminated string little in the string big, where not more than len characters are searched.
 *
 * Return:
 * If little is an empty string, big is returned; if little occurs nowhere in big, NULL is returned; otherwise a pointer to the first character of the first occurrence of little is returned.
 */
char *core_strnstr(const char *s1, const char *s2, size_t n)
{
    char *ptr_s1 = (char *)s1;
    char *ptr_s2 = (char *)s2;
    size_t it = n;

    while (n > 0 && *s1)
    {
        s1 = ptr_s1;
        s2 = ptr_s2;
        it = n;
        while (*s1 == *s2 && it-- > 0 && *s2++ && *s1++)
            ;
        if (!*s2)
            return (ptr_s1);
        ptr_s1++;
        n--;
    }
    return (NULL);
}
