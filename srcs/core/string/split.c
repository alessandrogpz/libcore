#include "libcore.h"

/* Counts the number of non-delimiter segments ('words') in 's'. */
size_t wordcount(char const *s, char c)
{
    size_t count = 0;
    int in_word = 0;

    while (*s)
    {
        if (*s != c && in_word == 0)
        {
            in_word = 1;
            count++;
        }
        else if (*s == c)
            in_word = 0;
        s++;
    }
    return (count);
}

/* Allocates and copies a single word from 's' starting at 'start'. */
static char *get_word(char const **s, char c)
{
    size_t len;
    char *word;
    char *start;

    // Advance *s past any leading delimiters to find the word's start
    while (**s && **s == c)
        (*s)++;

    start = (char *)*s;
    len = 0;
    // Calculate the length of the word
    while (*(*s + len) && *(*s + len) != c)
        len++;

    // Allocate memory for the word (+1 for null terminator)
    word = (char *)malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);

    // Copy the word using core_memcpy and null-terminate
    core_memcpy(word, start, len);
    word[len] = '\0';

    // Advance the main string pointer *s past the copied word
    *s += len;
    return (word);
}

/* Frees all previously allocated strings in the result array if a later malloc fails. */
static void free_result(char **result, size_t count)
{
    size_t i;

    i = 0;
    while (i < count)
    {
        free(result[i]);
        i++;
    }
    free(result);
}

/**
 * Description:
 * Allocates and returns an array of strings obtained by
 * splitting 's' using the character 'c' as a delimiter.
 * The array must end with a NULL pointer.
 *
 * Return:
 * The array of new strings resulting from the split.
 * NULL if the allocation fails.
 */
char **split(char const *s, char c)
{
    char **result;
    size_t word_count;
    size_t i;

    if (!s)
        return (NULL);

    word_count = wordcount(s, c);
    // Allocate for word_count words + 1 for the final NULL pointer
    result = (char **)malloc(sizeof(char *) * (word_count + 1));
    if (!result)
        return (NULL);

    i = 0;
    while (i < word_count)
    {
        // get_word handles skipping delimiters, copying, and advancing 's'
        result[i] = get_word(&s, c);
        if (!result[i])
        {
            // Clean up all memory allocated so far if malloc fails
            free_result(result, i);
            return (NULL);
        }
        i++;
    }

    result[word_count] = NULL;
    return (result);
}
