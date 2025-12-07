#include "libcore.h"

/**
 * Description:
 * Outputs the character 'c' to the specified file descriptor 'fd'.
 *
 * Return:
 * None (void).
 */
void putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}