#ifndef CORE_CTYPE_H
#define CORE_CTYPE_H

// Classification

int core_isalpha(int c);
int core_isdigit(int c);
int core_isalnum(int c);
int core_isascii(int c);
int core_isprint(int c);

// Conversion

int core_toupper(int c);
int core_tolower(int c);

#endif