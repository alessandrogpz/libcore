#ifndef PUT_H
#define PUT_H

#include <unistd.h>

/* ** File Descriptor Output Function */

void putchar_fd(char c, int fd);
void putstr_fd(char *s, int fd);
void putendl_fd(char *s, int fd);
void putnbr_fd(int n, int fd);

#endif