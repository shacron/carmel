#include <string.h>

char *strstr(const char *haystack, const char *needle) {
  size_t len = strlen(needle);
  if (len == 0) return (char*)haystack;
  for ( ; *haystack; haystack++) {
    if (!strncmp(haystack, needle, len)) return (char*)haystack;
  }
  return NULL;
}
