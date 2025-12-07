#include "libcore.h"

/**
 * Description:
 * Checks for any printable character including space.
 *
 * Return:
 * Non-zero if the character c falls into the tested class, and zero if not.
 */
int core_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
