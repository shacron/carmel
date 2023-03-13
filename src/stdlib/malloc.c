// SPDX-License-Identifier: MIT License
// Copyright (c) 2022 Shac Ron

#include <stdlib.h>
#include <string.h>

void *calloc(size_t count, size_t size) {
    void *p = malloc(size * count);
    if (p != NULL) memset(p, 0, size * count);
    return p;
}

void *malloc(size_t size) {
    return NULL;
}

void free(void *ptr) {

}
