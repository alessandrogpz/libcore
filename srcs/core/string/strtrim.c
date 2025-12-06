#include "includes.h"

/**
 * Description:
 * Allocates and returns a copy of the string 's1' with the characters
 * specified in 'set' removed from the beginning and the end of 's1'.
 *
 * Return:
 * A pointer to the new trimmed string, or NULL if the allocation fails.
 */
char *strtrim(char const *s1, char const *set)
{
    const char *start;
    const char *end;
    char *result;
    size_t len;

    if (!s1 || !set)
        return (NULL);

    if (!*set)
        return (core_strdup(s1));

    start = s1;
    // Find valid start
    while (*start && core_strchr(set, *start))
        start++;
    end = s1 + core_strlen(s1);

    // Find valid end (also after start)
    while (end > start && core_strchr(set, *(end - 1)))
        end--;

    // Edge case: Fully trimmed or empty input
    if (start >= end)
        len = 0;
    else
        len = end - start;

    result = (char *)malloc(sizeof(char) * (len + 1));
    if (!result)
        return (NULL);

    core_memcpy(result, start, len);

    result[len] = '\0';
    return (result);
}