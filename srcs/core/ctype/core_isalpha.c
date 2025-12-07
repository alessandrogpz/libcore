#include "libcore.h"

/**
 * Description:
 * Checks for an alphabetic character; in the standard "C" locale, it is equivalent to (isupper(c) || islower(c)).
 *
 * Return:
 * Non-zero if the character c falls into the tested class, and zero if not.
 */
int core_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
