#include "libcore.h"

/**
 * Description:
 * Outputs the null-terminated string 's' to the specified file descriptor 'fd',
 * immediately followed by a newline character ('\n').
 *
 * Return:
 * None (void).
 */
void putendl_fd(char *s, int fd)
{
    putstr_fd(s, fd);
    write(fd, "\n", 1);
}