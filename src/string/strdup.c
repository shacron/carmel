#include <string.h>

#include <stdlib.h>

char *strdup(const char *s) {
  size_t len = strlen(s) + 1;
  char *d = malloc(len);
  if (d) memcpy(d, s, len);
  return d;
}
