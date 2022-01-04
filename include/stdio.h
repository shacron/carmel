#pragma once

extern const char * const sys_errlist[];
extern const int sys_nerr;

int printf(const char * restrict format, ...);
int puts(const char *s);
