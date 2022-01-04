#include <string.h>

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
