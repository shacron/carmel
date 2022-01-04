#include <string.h>

int memcmp(const void *s1, const void *s2, size_t n) {
  const unsigned char *p1 = s1;
  const unsigned char *p2 = s2;
  for (size_t i = 0; i < n; i++) {
    int result = (int)p1[i] - (int)p2[i];
    if (result != 0) return result;
  }
  return 0;
}
