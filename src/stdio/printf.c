// SPDX-License-Identifier: MIT License
// Copyright (c) 2022-2023 Shac Ron

#include <stdbool.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

#include <carmel/platform.h>

// data type
#define TYPE_CHAR           (0)
#define TYPE_SIGNED         (1)
#define TYPE_UNSIGNED       (2)
#define TYPE_STRING         (3)
#define TYPE_ESCAPE         (4)

// format options
#define FLAG_LONG           (1u << 0)
#define FLAG_LONG_LONG      (1u << 1)
#define FLAG_HEX            (1u << 2)
#define FLAG_HEXPREFIX      (1u << 3)
#define FLAG_ZEROPAD        (1u << 4)

typedef struct {
    unsigned char type;
    unsigned char flags;
    unsigned int length;
    unsigned int pad;
} format_t;

static int print_decimal(format_t *f, unsigned long long num, bool neg);

static inline char hexchar(unsigned char c) {
    if (c < 10) return '0' + c;
    return 'a' + c - 10;
}

static int print_signed_decimal(format_t *f, long long num) {
    bool neg = false;
    if (num < 0) {
        neg = true;
        num = 0 - num;
    }
    return print_decimal(f, num, neg);
}

static inline int print_unsigned_decimal(format_t *f, unsigned long long num) {
    return print_decimal(f, num, false);
}

static int print_decimal(format_t *f, unsigned long long num, bool neg) {
    if (num == 0) {
        putchar('0');
        return 1;
    }

    int i;
    int count = 0;
    unsigned char dec[32];  // 2^64 = 20 decimal characters

    for (i = 0; num; i++) {
        unsigned char c = num % 10;
        num = num / 10;
        dec[i] = '0' + c;
    }
    if (neg) {
        dec[i] = '-';
        i++;
    }
    if (f->pad > i) {
        if (neg && (f->flags & FLAG_ZEROPAD)) {
            putchar('-');
            count++;
            i--;
            f->pad--;
        }
        const char pad_char = (f->flags & FLAG_ZEROPAD) ? '0' : ' ';
        for (int pad = f->pad; pad > i; pad--) {
            putchar(pad_char);
            count++;
        }
    }
    for (int s = i - 1; s >= 0; s--) {
        putchar(dec[s]);
        count++;
    }
    return count;
}

static int print_hex(format_t *f, unsigned long long val) {
    const int val_bits = sizeof(val) * CHAR_BIT;
    int count = 0;
    int num_chars = 1;
    const char pad_char = (f->flags & FLAG_ZEROPAD) ? '0' : ' ';

    if (val != 0) num_chars = ((val_bits - __builtin_clzll(val)) + 3) / 4;

    if ((f->flags & FLAG_HEXPREFIX) == 0) {
        for (unsigned int pad = f->pad; pad > num_chars; pad--) {
            putchar(pad_char);
            count++;
        }
        goto print_num;
    }
    if (f->flags & FLAG_ZEROPAD) {
        putchar('0');
        putchar('x');
        count += 2;
        for (unsigned int pad = f->pad; pad > num_chars + 2; pad--) {
            putchar(pad_char);
            count++;
    }
    } else {
        for (unsigned int pad = f->pad; pad > num_chars + 2; pad--) {
            putchar(pad_char);
            count++;
        }
        putchar('0');
        putchar('x');
        count += 2;
    }

print_num:
    if (val == 0) {
        putchar('0');
        count++;
    } else {
        val <<= (val_bits - (num_chars * 4));
        for (int s = 0; s < num_chars; s++) {
            unsigned char c = (unsigned char)(val >> (val_bits - 4));
            val <<= 4;
            putchar(hexchar(c));
            count++;
        }
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

static int parse_format(format_t *f, const char *s) {
    unsigned int i = 0;

    if (s[i] != '%') return -1;
    i++;

    if (s[i] == '\0') return -1;
    if (s[i] == '%') {
        f->length = i+1;
        f->flags = TYPE_ESCAPE;
        return 0;
    }
    if (s[i] == '#') {
        f->flags = FLAG_HEXPREFIX;
        i++;
    }
    if (s[i] == '0') {
        f->flags |= FLAG_ZEROPAD;
        i++;
    }

    while ((s[i] >= '0') && (s[i] <= '9')) {
        f->pad = (f->pad * 10) + (s[i] - '0');
        i++;
    }
    if (s[i] == '\0') return -1;

    // z or ll qualifiers
    if (s[i] == 'z') {
        f->flags |= FLAG_LONG;
        i++;
    } else if (s[i] == 'l') {
        f->flags |= FLAG_LONG;
        i++;
        if (s[i] == 'l') {
            f->flags |= FLAG_LONG_LONG;
            i++;
        }
    }
    if (s[i] == '\0') return -1;

    switch (s[i]) {
    case 'c':
        f->type = TYPE_CHAR;
        break;

    case 'd':
    case 'i':
        f->type = TYPE_SIGNED;
        break;

    case 'x':
        f->flags |= FLAG_HEX;
    case 'u':
        f->type = TYPE_UNSIGNED;
        break;

    case 's':
        f->type = TYPE_STRING;
        break;

    case 'p':
        f->type = TYPE_UNSIGNED;
        f->flags |= FLAG_HEX | FLAG_LONG;
        break;

    default:
        return -1;
    }
    f->length = i + 1;
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
    const char *s = format;
    int i = 0;
    int count = 0;

    for ( ; ; ) {
        if (s[i] == '\0') return count;
        if (s[i] != '%') {
            putchar(s[i]);
            i++;
            count++;
            continue;
        }
        format_t f = {};
        if (parse_format(&f, s+i)) {
            putchar('%');
            count++;
            i++;
            continue;
        }

        unsigned long long arg;
        switch (f.type) {
        case TYPE_CHAR:
        {
            int c = va_arg(ap, int);
            putchar(c);
            count++;
            i += f.length;
            break;
        }

        case TYPE_SIGNED:
        {
            long long sarg;
            if (f.flags & FLAG_LONG_LONG) sarg = va_arg(ap, long long);
            else if (f.flags & FLAG_LONG) sarg = va_arg(ap, long);
            else sarg = va_arg(ap, int);
            count += print_signed_decimal(&f, sarg);
            i += f.length;
            break;
        }

        case TYPE_UNSIGNED:
            if (f.flags & FLAG_LONG_LONG) arg = va_arg(ap, unsigned long long);
            else if (f.flags & FLAG_LONG) arg = va_arg(ap, unsigned long);
            else arg = va_arg(ap, unsigned int);
            if (f.flags & FLAG_HEX) {
                count += print_hex(&f, arg);
            } else {
                count += print_unsigned_decimal(&f, arg);
            }
            i += f.length;
            break;

        case TYPE_STRING:
        {
            char *s = va_arg(ap, char *);
            if (s == NULL) s = "<NULL>";
            for ( ; *s; s++) putchar(*s);
            i += f.length;
            break;
        }

        default:
        case TYPE_ESCAPE:
            putchar('%');
            count++;
            i += f.length;
            break;
        }
    }
}


