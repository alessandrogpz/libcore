#include "includes.h"

/**
 * Description:
 * Outputs the integer 'n' to the specified file descriptor 'fd'.
 * It handles positive, negative, and zero values by converting the
 * integer to its string representation.
 *
 * Return:
 * None (void).
 */
void putnbr_fd(int n, int fd)
{
    char *s;
    size_t len;

    s = itoa(n);

    if (!s)
        return;

    len = core_strlen(s);
    write(fd, s, len);
}