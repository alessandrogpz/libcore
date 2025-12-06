#include "includes.h"

/**
 * Description:
 * allocates memory for an array of elements and initializes all bytes of the allocated memory to zero.
 *
 * Arguments:
 *  It takes two arguments, the number of elements and the size of each element
 *
 * Return:
 * void* pointer to the allocated memory or a null pointer if allocation fails.
 */
void *core_calloc(size_t elm_count, size_t elm_size)
{
    size_t total_size;
    void *arr;

    total_size = elm_count * elm_size;

    if (elm_count != 0 && total_size / elm_count != elm_size)
        return (NULL);

    arr = malloc(total_size);

    if (!arr)
        return (NULL);

    core_memset(arr, 0, total_size);
    return (arr);
}