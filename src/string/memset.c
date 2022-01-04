#include <string.h>

void *memset(void *b, int c, size_t len) {
  unsigned char *d = b;
  for (size_t i = 0; i < len; i++) d[i] = (unsigned char)c;
  return b;
}
