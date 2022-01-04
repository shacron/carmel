#include <string.h>

char *strncpy(char *dst, const char *src, size_t len) {
  size_t i;
  for (i = 0; i < len; i++) {
    dst[i] = src[i];
    if (src[i] == '\0') {
      for (i++; i < len; i++) dst[i] = '\0';
      break;
    }
  }
  return dst;
}
