#include <string.h>

void *memchr(const void *s, int c, size_t n) {
  const unsigned char *str = s;
  for (size_t i = 0; i < n; i++) {
    if (str[i] == (unsigned char)c) return (void*)&str[i];
  }
  return NULL;
}
