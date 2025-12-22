#include "libcore.h"

/**
 * Description:
 * Validates and prints the arguments passed to it, similar to the standard printf.
 * str  : The string format to print.
 * ...  : The variadic arguments to print.
 *
 * Supported formats:
 * %c, %s, %p, %d, %i, %u, %x, %X, %%
 *
 * Return:
 * The total number of characters printed.
 */
int core_printf(const char *str, ...)
{
	int i;
	int total_len;
	va_list args;

	i = 0;
	total_len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			total_len += formats(args, str[i + 1]);
			i++;
		}
		else
			total_len += putchar_len(str[i]);
		i++;
	}
	va_end(args);
	return (total_len);
}
