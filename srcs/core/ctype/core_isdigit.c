#include "includes.h"

/**
 * Description:
 * Checks for a digit (0 through 9).
 *
 * Return:
 * Non-zero if the character c falls into the tested class, and zero if not.
 */
int core_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
