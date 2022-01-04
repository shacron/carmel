#include <string.h>

int strncmp(const char *s1, const char *s2, size_t n) {
  for (size_t i = 0; i < n; i++) {
    int result = (int)s1[i] - (int)s2[i];
    if (result != 0) return result;
    if (s1[i] == '\0') break;
  }
  return 0;
}
