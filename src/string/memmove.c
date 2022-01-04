#include <string.h>

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