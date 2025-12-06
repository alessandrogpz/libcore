#ifndef CORE_MEMORY_H
#define CORE_MEMORY_H

#include <stddef.h>
#include <stdlib.h>

/* ** Raw Memory Manipulation
** These operate on void pointers and require a specific size 'n'.
*/

void *core_memset(void *s, int c, size_t n);
void core_bzero(void *s, size_t n);
void *core_memcpy(void *dest, const void *src, size_t n);
void *core_memmove(void *dest, const void *src, size_t n);
void *core_memchr(const void *s, int c, size_t n);
int core_memcmp(const void *s1, const void *s2, size_t n);

/* ** Memory Allocation */

void *core_calloc(size_t nelem, size_t elsize);

#endif