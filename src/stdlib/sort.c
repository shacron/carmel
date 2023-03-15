// SPDX-License-Identifier: MIT License
// Copyright (c) 2023 Shac Ron

#include <stdlib.h>

static void mem_swap(char * restrict a, char * restrict b, size_t len) {
    for (size_t i = 0; i < len; i++) {
        char tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

void qsort(void *base, size_t num, size_t width, int (*compare)(const void *, const void *)) {
    if (num <= 1) return;
    if (num == 2) {
        int cmp = compare(base, base + width);
        if (cmp <= 0) return;
        mem_swap(base, base + width, width);
        return;
    }

    size_t p = num / 2;
    size_t a = 0;
    size_t b = num - 1;
    for ( ; a < b; ) {
        if (a < p) {
            for ( ; a < p; a++) {
                int cmp = compare(base + (a * width), base + (p * width));
                if (cmp > 0) break;
            }
            if (a < p) {
                mem_swap(base + (a * width), base + (p * width), width);
                p = a;
            }
        }
        if (b > p) {
            for ( ; b > p; b--) {
                int cmp = compare(base + (b * width), base + (p * width));
                if (cmp < 0) break;
            }
            if (b > p) {
                mem_swap(base + (b * width), base + (p * width), width);
                p = b;
            }
        }
    }
    qsort(base, p, width, compare);
    qsort(base + (p * width), num - p, width, compare);
}

void qsort_r(void *base, size_t num, size_t width, void *thunk, int (*compare)(void *, const void *, const void *)) {
    if (num <= 1) return;
    if (num == 2) {
        int cmp = compare(thunk, base, base + width);
        if (cmp <= 0) return;
        mem_swap(base, base + width, width);
        return;
    }

    size_t p = num / 2;
    size_t a = 0;
    size_t b = num - 1;
    for ( ; a < b; ) {
        if (a < p) {
            for ( ; a < p; a++) {
                int cmp = compare(thunk, base + (a * width), base + (p * width));
                if (cmp > 0) break;
            }
            if (a < p) {
                mem_swap(base + (a * width), base + (p * width), width);
                p = a;
            }
        }
        if (b > p) {
            for ( ; b > p; b--) {
                int cmp = compare(thunk, base + (b * width), base + (p * width));
                if (cmp < 0) break;
            }
            if (b > p) {
                mem_swap(base + (b * width), base + (p * width), width);
                p = b;
            }
        }
    }
    qsort_r(base, p, width, thunk, compare);
    qsort_r(base + (p * width), num - p, width, thunk, compare);
}
