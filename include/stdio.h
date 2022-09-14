#pragma once

#include <stdarg.h>

extern const char * const sys_errlist[];
extern const int sys_nerr;

int putchar(int c);
int puts(const char *s);

int printf(const char * restrict format, ...) __attribute__((__format__ (__printf__, 1, 2)));
int vprintf(const char * restrict format, va_list ap);
