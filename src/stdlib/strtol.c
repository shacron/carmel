// MIT License

// Copyright (c) 2022 Shac Ron

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// SPDX-License-Identifier: MIT License

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

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
        char c = *s;
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
        char c = *s;
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

