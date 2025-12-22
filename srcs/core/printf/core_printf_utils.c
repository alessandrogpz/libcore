#include "libcore.h"

/**
 * Description:
 * Write a single character to stdout and return number of bytes written.
 * c    : The character to write
 *
 * Return:
 * Number of bytes written (1 on success, -1 on error)
 */
int putchar_len(char c)
{
	return (write(1, &c, 1));
}

/**
 * Description:
 * Recursive function to print ANY number in ANY base
 * n    : The number to print (unsigned long to handle %p and %u)
 * base : The symbols (e.g., "0123456789" or "0123456789abcdef")
 *
 * Return:
 * Number of characters printted
 */
int putnbr_base(unsigned long long n, char *base)
{
	int count;
	unsigned long long base_len;

	count = 0;
	base_len = 0;
	while (base[base_len])
		base_len++;
	if (n >= base_len)
		count += putnbr_base(n / base_len, base);
	count += putchar_len(base[n % base_len]);
	return (count);
}

/**
 * Description:
 * Write a null-terminated string to stdout and return the number of characters printed.
 * s    : Pointer to the string to print (may be NULL)
 *
 * Return:
 * Number of characters printed (or number of bytes written for "(null)" when s is NULL)
 */
int putstr_len(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[i])
		write(1, &s[i++], 1);
	return (i);
}

/**
 * Description:
 * Print a signed integer in base 10 and return the number of characters printed.
 * n    : The integer to print
 *
 * Return:
 * Number of characters printed
 */
int putnbr_len(int n)
{
	int count;
	long nb;

	count = 0;
	nb = n;
	if (nb < 0)
	{
		count += write(1, "-", 1);
		nb = -nb;
	}
	count += putnbr_base(nb, "0123456789");
	return (count);
}

/**
 * Description:
 * Print a pointer value in hexadecimal with '0x' prefix and return the number of characters printed.
 * ptr  : The pointer to print (may be NULL)
 *
 * Return:
 * Number of characters printed
 */
int putptr_len(void *ptr)
{
	int count;

	count = 0;
	if (!ptr)
		return (write(1, "(nil)", 5));
	count += write(1, "0x", 2);
	count += putnbr_base((unsigned long long)ptr, "0123456789abcdef");
	return (count);
}

/**
 * Description:
 * Handle a single printf-style format specifier by fetching the appropriate argument and printing it.
 * args   : The variadic argument list
 * format : The format specifier character (e.g., 's', 'd', 'x', etc.)
 *
 * Return:
 * Number of characters printed for this specifier
 */
int formats(va_list args, const char format)
{
	int len;

	len = 0;
	if (format == 'c')
		len += putchar_len(va_arg(args, int));
	else if (format == 's')
		len += putstr_len(va_arg(args, char *));
	else if (format == 'p')
		len += putptr_len(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		len += putnbr_len(va_arg(args, int));
	else if (format == 'u')
		len += putnbr_base(va_arg(args, unsigned int), "0123456789");
	else if (format == 'x')
		len += putnbr_base(va_arg(args, unsigned int), "0123456789abcdef");
	else if (format == 'X')
		len += putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (format == '%')
		len += putchar_len('%');
	return (len);
}
