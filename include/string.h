#pragma once

#include <stddef.h>

void *memccpy(void *restrict dst, const void *restrict src, int c, size_t n);
void *memchr(const void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *restrict dst, const void *restrict src, size_t n);
void *memmove(void *dst, const void *src, size_t len);
void *memset(void *b, int c, size_t len);
char *strcat(char *restrict s1, const char *restrict s2);
char *strchr(const char *s, int c);
int strcmp(const char *s1, const char *s2);
int strcoll(const char *s1, const char *s2);
char *strcpy(char *dst, const char * src);
size_t strcspn(const char *s, const char *charset);
char *strdup(const char *s);
char *strerror(int errnum);
char *strncat(char *restrict s1, const char *restrict s2, size_t n);
char *strncpy(char *dst, const char *src, size_t len);
size_t strlen(const char *s);
int strncmp(const char *s1, const char *s2, size_t n);
char *strpbrk(const char *s, const char *charset);
char *strrchr(const char *s, int c);
size_t strspn(const char *s, const char *charset);
char *strstr(const char *haystack, const char *needle);

// use strsep() if available
char *strtok(char *restrict str, const char *restrict sep);

#if __BSD_EXT_STRING
char *strsep(char **stringp, const char *delim);
#endif
