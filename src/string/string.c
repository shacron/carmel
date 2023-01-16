// SPDX-License-Identifier: MIT License
// Copyright (c) 2022-2023 Shac Ron

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void *memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    char *d = dst;
    const char *s = src;
    for (size_t i = 0; i < n; i++) {
        d[i] = s[i];
        if (s[i] == (unsigned char)c) return &d[i+1];
    }
    return NULL;
}

void *memchr(const void *s, int c, size_t n) {
    const unsigned char *str = s;
    for (size_t i = 0; i < n; i++) {
        if (str[i] == (unsigned char)c) return (void*)&str[i];
    }
    return NULL;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *p1 = s1;
    const unsigned char *p2 = s2;
    for (size_t i = 0; i < n; i++) {
        int result = (int)p1[i] - (int)p2[i];
        if (result != 0) return result;
    }
    return 0;
}

void *memcpy(void *restrict dst, const void *restrict src, size_t n) {
    char *d = dst;
    const char *s = src;
    for (size_t i = 0; i < n; i++) d[i] = s[i];
    return dst;
}

void *memmove(void *dst, const void *src, size_t len) {
    if (dst == src) return dst;
    char *d = dst;
    const char *s = src;
    if (d < s) {
        for (size_t i = 0; i < len; i++) d[i] = s[i];
    } else {
        for (size_t i = len; i > 0; ) {
            i--;
            d[i] = s[i];
        }
    }
    return dst;
}

void *memset(void *b, int c, size_t len) {
    unsigned char *d = b;
    for (size_t i = 0; i < len; i++) d[i] = (unsigned char)c;
    return b;
}

char *strcat(char *restrict s1, const char *restrict s2) {
    char *d = s1;
    while (*d) d++;
    while ((*d++ = *s2++)) ;
    return s1;
}

char *strchr(const char *s, int c) {
    for ( ; *s != (char)c; s++) {
        if (*s == '\0') return NULL;
    }
    return (char *)s;
}

int strcoll(const char *s1, const char *s2) {
    return strcmp(s1, s2);
}

int strcmp(const char *s1, const char *s2) {
    for ( ; ; s1++, s2++) {
        int result = (int)*s1 - (int)*s2;
        if (result != 0) return result;
        if (*s1 == '\0') return 0;
    }
}

int strcasecmp(const char *s1, const char *s2) {
    for ( ; ; s1++, s2++) {
        int result = toupper((int)*s1) - toupper((int)*s2);
        if (result != 0) return result;
        if (*s1 == '\0') return 0;
    }
}

char *strcpy(char *dst, const char *src) {
    char *d = dst;
    while((*d++ = *src++)) ;
    return dst;
}

size_t strcspn(const char *s, const char *charset) {
    size_t i;
    for (i = 0; s[i] != '\0'; i++) {
        for (size_t j = 0; charset[j] != '\0'; j++) {
            if (s[i] == charset[j]) goto found;
        }
        return i;
found:
        continue;
    }
    return i;
}

char *strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *d = malloc(len);
    if (d) memcpy(d, s, len);
    return d;
}

char *strndup(const char *s, size_t n) {
    size_t len = strlen(s);
    if (len > n) len = n;
    char *d = malloc(len + 1);
    if (d) {
        memcpy(d, s, len);
        d[len] = '\0';
    }
    return d;
}

size_t strlen(const char *s) {
    size_t i;
    for (i = 0; s[i] != '\0'; i++) ;
    return i;
}

char *strncat(char *restrict s1, const char *restrict s2, size_t n) {
    char *d = s1;
    while (*d) d++;
    size_t i;
    for (i = 0; i < n; i++) {
        d[i] = s2[i];
        if (d[i] == '\0') return s1;
    }
    d[i] = '\0';
    return s1;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        int result = (int)s1[i] - (int)s2[i];
        if (result != 0) return result;
        if (s1[i] == '\0') break;
    }
    return 0;
}

int strncasecmp(const char *s1, const char *s2, size_t n) {
    for (size_t i = 0; i < n; i++) {
        int result = toupper(s1[i]) - toupper(s2[i]);
        if (result != 0) return result;
        if (s1[i] == '\0') break;
    }
    return 0;
}

char *strncpy(char *dst, const char *src, size_t n) {
    size_t i;
    for (i = 0; i < n; i++) {
        dst[i] = src[i];
        if (src[i] == '\0') {
            for (i++; i < n; i++) dst[i] = '\0';
            break;
        }
    }
    return dst;
}

char *strpbrk(const char *s, const char *charset) {
    for ( ; *s; s++) {
        for (size_t j = 0; charset[j] != '\0'; j++) {
            if (*s == charset[j]) return (char*)s;
        }
    }
    return NULL;
}

char *strrchr(const char *s, int c) {
    const char *last = NULL;
    for ( ; *s; s++) {
        if (*s == (char)c) last = s;
    }
    return (char*)last;
}

size_t strspn(const char *s, const char *charset) {
    size_t i;
    for (i = 0; s[i] != '\0'; i++) {
        for (size_t j = 0; charset[j] != '\0'; j++) {
            if (s[i] == charset[j]) return i;
        }
    }
    return i;
}

char *strstr(const char *haystack, const char *needle) {
    size_t len = strlen(needle);
    if (len == 0) return (char*)haystack;
    for ( ; *haystack; haystack++) {
        if (!strncmp(haystack, needle, len)) return (char*)haystack;
    }
    return NULL;
}

#if CARMEL_UNSAFE_STRING
char *strtok(char *restrict str, const char *restrict sep) {
    static char *lasts;
    return strtok_r(str, sep, &lasts);
}
#endif

char *strtok_r(char *restrict s, const char *restrict sep, char **restrict lasts) {
    if (s == NULL) {
        s = *lasts;
        if (s == NULL) return NULL;
    }

    int found = 0;
    for (char *p = s; *p; p++) {
        for (int i = 0; sep[i] != '\0'; i++) {
            if (*p == sep[i]) {
                *p = '\0';
                found = 1;
                goto outer_continue;
            }
        }
        if (found) {
            *lasts = p;
            return s;
        }
outer_continue:
        (void)0;
    }

    *lasts = NULL;
    return s;
}

