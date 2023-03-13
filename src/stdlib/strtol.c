// SPDX-License-Identifier: MIT License
// Copyright (c) 2022 Shac Ron

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

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
        val = val * b + add;
        valid = true;
        lc = s;
        if (neg) {
            if (val > ((unsigned long)LONG_MAX + 1)) {
                val = LONG_MIN;
                neg = false;
                errno = ERANGE;
                break;
            }
        } else {
            if (val > LONG_MAX) {
                val = LONG_MAX;
                errno = ERANGE;
                break;
            }
        }
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
}

