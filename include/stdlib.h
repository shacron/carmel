#pragma once

#include <stddef.h>

_Noreturn void abort(void);

void *calloc(size_t count, size_t size);
void free(void *ptr);
void *malloc(size_t size);
