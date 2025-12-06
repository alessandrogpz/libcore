#include "includes.h"

/**
 * Description:
 * Outputs the null-terminated string 's' to the specified file descriptor 'fd'.
 *
 * Return:
 * None (void).
 */
void putstr_fd(char *s, int fd)
{
    while (*s)
        write(fd, s++, 1);
}