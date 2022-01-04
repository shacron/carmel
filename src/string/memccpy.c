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
