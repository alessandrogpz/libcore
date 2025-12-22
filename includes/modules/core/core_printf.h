#ifndef CORE_PRINTF_H
#define CORE_PRINTF_H

#include <stdarg.h>
#include <unistd.h>

int putchar_len(char c);
int putnbr_base(unsigned long long n, char *base);
int putstr_len(char *s);
int putnbr_len(int n);
int putptr_len(void *ptr);
int formats(va_list args, const char format);
int core_printf(const char *str, ...);

#endif