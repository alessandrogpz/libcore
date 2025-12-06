#ifndef CORE_STRING_H
#define CORE_STRING_H

#include <stddef.h>
#include <stdlib.h>

/* ** String Length & Conversion */

size_t core_strlen(const char *str);
int core_atoi(const char *n);
char *itoa(int n);

/* ** String Copying & Concatenation */

size_t core_strlcpy(char *dst, const char *src, size_t dsize);
size_t core_strlcat(char *dst, const char *src, size_t dsize);
char *core_strdup(const char *s);

/* ** String Comparison */

int core_strncmp(const char *s1, const char *s2, size_t n);

/* ** String Search */

char *core_strchr(const char *s, int c);
char *core_strrchr(const char *s, int c);
char *core_strnstr(const char *s1, const char *s2, size_t n);

/* ** String generation */

char *substr(char const *s, unsigned int start, size_t len);
char *strjoin(char const *s1, char const *s2);
char *strtrim(char const *s1, char const *set);
char **split(char const *s, char c);

/* ** String Iteration / Mapping */

char *strmapi(char const *s, char (*f)(unsigned int, char));
void striteri(char *s, void (*f)(unsigned int, char *));

#endif