#include "includes.h"

/**
 * Description:
 * Calculates the length of the string s, excluding the terminating null byte ('\0').
 *
 * Return:
 * The number of bytes in the string s.
 */
size_t core_strlen(const char *str)
{
	const char *ptr;

	ptr = str;
	while (*ptr)
		ptr++;
	return (ptr - str);
}
