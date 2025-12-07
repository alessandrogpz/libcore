#include "libcore.h"

/**
 * Descrtiption:
 * Allocates and returns a new string, which is the result of the
 * concatenation of 's1' and 's2'.
 *
 * Return:
 * A pointer to the new concatenated string, or NULL if
 * the allocation fails or if s1/s2 are NULL.
 **/
char *strjoin(char const *s1, char const *s2)
{
    size_t s1_len;
    size_t s2_len;
    char *result;
    char *head;

    if (!s1 || !s2)
        return (NULL);

    s1_len = core_strlen(s1);
    s2_len = core_strlen(s2);

    result = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
    if (!result)
        return (NULL);

    head = result;

    while (*s1)
        *result++ = *s1++;
    while (*s2)
        *result++ = *s2++;

    *result = '\0';
    return (head);
}