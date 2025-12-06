#include "includes.h"

/**
 * Description:
 * Checks whether c is a 7-bit unsigned char value that fits into the ASCII character set.
 *
 * Return:
 * Non-zero if the character c falls into the tested class, and zero if not.
 */
int core_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
