// SPDX-License-Identifier: MIT License
// Copyright (c) 2022 Shac Ron

#include <stdlib.h>

int abs(int n) {
    if (n < 0) return -n;
    return n;
}

long labs(long n) {
    if (n < 0) return -n;
    return n;
}

div_t div(int numer, int denom) {
    div_t d;
    d.quot = numer / denom;
    d.rem = numer % denom;
    return d;
}

ldiv_t ldiv(long numer, long denom) {
    ldiv_t d;
    d.quot = numer / denom;
    d.rem = numer % denom;
    return d;
}
