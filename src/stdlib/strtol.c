// SPDX-License-Identifier: MIT License
// Copyright (c) 2022-2026 Shac Ron

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

#include <carmel/utils.h>

int atoi(const char *s) {
    return (int)strtol(s, (char **)NULL, 10);
}

long atol(const char *s) {
    return strtol(s, (char **)NULL, 10);
}

long strtol(const char *restrict s, char **restrict endptr, int base) {
    unsigned int b = base;
    if ((b == 1) || (b > 36)) {
        errno = EINVAL;
        return 0;
    }

    const char *lc = s - 1;

    while (isspace(*s)) s++;

    unsigned long val = 0;
    bool neg = false;
    bool valid = false;

    if (*s == '-') {
        s++;
        neg = true;
    } else if (*s == '+') {
        s++;
    }

    // consume initial 0 or 0x
    if (*s == '0') {
        lc = s;
        s++;
        valid = true;

        if ((b == 0) || (b == 16)) {
            if (*s == 'x') {
                s++;
                b = 16;
            }
        }
        if (b == 0) b = 8;
    } else {
        if (b == 0) b = 10;
    }

    for ( ; *s != '\0'; s++) {
        unsigned char c = *s;
        unsigned int add = 0;
        if ((c >= '0') && (c <= '9')) add = c - '0';
        else {
            if (c <= 'Z') c += ('a' - 'A');
            if ((c >= 'a') && (c <= 'z')) add = c - 'a' + 10;
            else break;
        }
        if (add >= b) break;

        // val = val * b + add;
        unsigned long v;
        if (carmel_mul_overflow_ulong(val, b, &v)) goto overflow;
        if (carmel_add_overflow_ulong(v, add, &val)) goto overflow;
        valid = true;
        lc = s;
    }

    // munch remaining
    for ( ; *s != '\0'; s++) {
        unsigned char c = *s;
        unsigned int add = 0x100;
        if ((c >= '0') && (c <= '9')) add = c - '0';
        else {
            if (c <= 'Z') c += ('a' - 'A');
            if ((c >= 'a') && (c <= 'z')) add = c - 'a' + 10;
        }
        if (add >= b) break;
        lc = s;
    }

    if (!valid) errno = EINVAL;
    if (endptr) *endptr = (char *)(lc + 1);
    if (neg) return -val;
    return val;

overflow:
    if (neg) val = LONG_MIN;
    else     val = LONG_MAX;
    errno = ERANGE;
    return val;
}

