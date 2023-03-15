#pragma once

#include <stddef.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

_Noreturn void abort(void);
void exit(int status);
void _Exit(int status);

void *calloc(size_t count, size_t size);
void free(void *ptr);
void *malloc(size_t size);

int atoi(const char *s);
long atol(const char *s);
long strtol(const char *restrict s, char **restrict endptr, int base);

int abs(int n);
long int labs(long int n);

typedef struct {
    int quot;
    int rem;
} div_t;

typedef struct {
    long quot;
    long rem;
} ldiv_t;

div_t div(int numer, int denom);
ldiv_t ldiv(long numer, long denom);

void qsort(void *base, size_t num, size_t width, int (*compare)(const void *, const void *));
void qsort_r(void *base, size_t num, size_t width, void *thunk, int (*compare)(void *, const void *, const void *));
