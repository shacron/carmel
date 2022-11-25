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

#include <limits.h>
#include <stddef.h>
#include <stdio.h>

#include <carmel/platform.h>

#define FLAG_LONG       (1u << 0)
#define FLAG_LONG_LONG  (1u << 1)
#define FLAG_CHAR       (1u << 2)
#define FLAG_SIZE_T     (1u << 3)
#define FLAG_UNSIGNED   (1u << 4)
#define FLAG_HEX        (1u << 5)

static int print_unsigned_decimal(unsigned long long num);

static char hexchar(unsigned char c) {
    if (c < 10) return '0' + c;
    return 'a' + c - 10;
}

static int print_signed_decimal(long long num) {
    int count = 0;
    if (num < 0) {
        putchar('-');
        count = 1;
        num = 0 - num;
    }
    return print_unsigned_decimal(num) + count;
}

static int print_unsigned_decimal(unsigned long long num) {
    if (num == 0) {
        putchar('0');
        return 1;
    }
    int count;
    unsigned char dec[40];

    for (count = 0; num; count++) {
        unsigned char c = num % 10;
        num = num / 10;
        dec[count] = '0' + c;
    }
    for (int i = count - 1; i >= 0; i--) {
        putchar(dec[i]);
    }
    return count;
}

static int print_hex(unsigned long long val) {
    int i;
    const int val_chars = 2 * sizeof(val);
    const int val_bits = sizeof(val) * CHAR_BIT;

    // consume leading zeros
    for (i = 0; i < val_chars; i++) {
        unsigned char c = (unsigned char)(val >> (val_bits - 4));
        if (c != 0) break;
        val <<= 4;
    }
    if (i == val_chars) {
        putchar('0');
        return 1;
    }

    int count = val_chars - i;
    for ( ; i < val_chars; i++) {
        unsigned char c = (unsigned char)(val >> (val_bits - 4));
        val <<= 4;
        putchar(hexchar(c));
    }
    return count;
}

int getchar(void) {
    return platform_getchar();
}

int putchar(int c) {
    platform_putchar(c);
    return 0;
}

int puts(const char *s) {
    for ( ; *s; s++) putchar(*s);
    putchar('\n');
    return 0;
}

int printf(const char * restrict format, ...) {
    va_list ap;
    va_start(ap, format);
    int result = vprintf(format, ap);
    va_end(ap);
    return result;
}

int vprintf(const char * restrict format, va_list ap) {
    const char *f = format;
    int count = 0;
    for ( ; ; ) {
        char b, a = *f;
        if (a == '\0') return count;
        f++;

        if (a != '%') {
            putchar(a);
            count++;
            continue;
        }

        unsigned int flags = 0;
        unsigned long long arg;

next_flag:
        b = *f;
        f++;

        switch (b) {
        case '\0': return count;

        case '%':
        default:
            putchar(b);
            count++;
            continue;

        // flag characters
        case 'l':
            if (flags & FLAG_LONG) flags |= FLAG_LONG_LONG;
            else flags |= FLAG_LONG;
            goto next_flag;

        case 'z':
            flags |= FLAG_LONG; // todo FLAG_SIZE_T
            goto next_flag;

        // format characters

        case 's':
        {
            char *s = va_arg(ap, char *);
            if (s == NULL) s = "<NULL>";
            for ( ; *s; s++) putchar(*s);
            break;
        }

        case 'c':
        {
            int c = va_arg(ap, int);
            putchar(c);
            count++;
            break;
        }

        case 'd':
        case 'i':
        {
            long long sarg;
            if (flags & FLAG_LONG_LONG) sarg = va_arg(ap, long long);
            else if (flags & FLAG_LONG) sarg = va_arg(ap, long);
            else sarg = va_arg(ap, int);
            count += print_signed_decimal(sarg);
            break;
        }

        case 'u':
            if (flags & FLAG_LONG_LONG) arg = va_arg(ap, unsigned long long);
            else if (flags & FLAG_LONG) arg = va_arg(ap, unsigned long);
            else arg = va_arg(ap, unsigned int);
            count += print_unsigned_decimal(arg);
            break;

        case 'p':
            flags = FLAG_LONG;
        case 'x':
            if (flags & FLAG_LONG_LONG) arg = va_arg(ap, unsigned long long);
            else if (flags & FLAG_LONG) arg = va_arg(ap, unsigned long);
            else arg = va_arg(ap, unsigned int);
            count += print_hex(arg);
            break;
        }
    }
}


