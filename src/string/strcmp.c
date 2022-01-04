#include <string.h>

int strcmp(const char *s1, const char *s2) {
  for ( ; ; s1++, s2++) {
    int result = (int)*s1 - (int)*s2;
    if (result != 0) return result;
    if (*s1 == '\0') return 0;
  }
}
