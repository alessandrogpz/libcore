#include "libcore.h"

/**
 * Description:
 * Checks for an alphanumeric character; it is equivalent to (isalpha(c) || isdigit(c)).
 *
 * Return:
 * Non-zero if the character c falls into the tested class, and zero if not.
 */
int core_isalnum(int c)
{
	if (core_isalpha(c) || core_isdigit(c))
		return (1);
	return (0);
}
