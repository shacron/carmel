#include <stdio.h>

#define FLAG_LONG       (1u << 0)
#define FLAG_LONG_LONG  (1u << 1)
#define FLAG_CHAR       (1u << 2)
#define FLAG_SIZE_T     (1u << 3)
#define FLAG_UNSIGNED   (1u << 4)
#define FLAG_HEX        (1u << 5)

extern void platform_putchar(char c);

static int print_unsigned_decimal(unsigned long num);

static char hexchar(unsigned char c) {
    if (c < 10) return '0' + c;
    return 'a' + c - 10;
}

static int print_signed_decimal(long num) {
    int count = 0;
    if (num < 0) {
        putchar('-');
        count = 1;
        num = 0 - num;
    }
    return print_unsigned_decimal(num) + count;
}

static int print_unsigned_decimal(unsigned long num) {
    if (num == 0) {
        putchar('0');
        return 1;
    }
    int count;
    unsigned char dec[22];
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

static int print_hex(unsigned long num) {
    int i;

    // consume leading zeros
    for (i = 0; i < 16; i++) {
        unsigned char c = (unsigned char)(num >> 60);
        if (c != 0) break;
        num <<= 4;
    }
    if (i == 16) {
        putchar('0');
        return 1;
    }

    int count = 16 - i;
    for ( ; i < 16; i++) {
        unsigned char c = (unsigned char)(num >> 60);
        num <<= 4;
        putchar(hexchar(c));
    }
    return count;
}

int putchar(int c) {
  platform_putchar(c);
  return 0;
}

int puts(const char *s) {
  for ( ; *s; s++) putchar(*s);
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
        unsigned long arg;

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
            long sarg;
            if (flags & FLAG_LONG) sarg = va_arg(ap, long);
            else sarg = va_arg(ap, int);
            count += print_signed_decimal(sarg);
            break;
        }

        case 'u':
            if (flags & FLAG_LONG) arg = va_arg(ap, unsigned long);
            else arg = va_arg(ap, unsigned int);
            count += print_unsigned_decimal(arg);
            break;

        case 'p':
            flags = FLAG_LONG;
        case 'x':
            if (flags & FLAG_LONG) arg = va_arg(ap, unsigned long);
            else arg = va_arg(ap, unsigned int);
            count += print_hex(arg);
            break;
        }
    }
}

