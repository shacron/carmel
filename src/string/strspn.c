#include <string.h>

size_t strspn(const char *s, const char *charset) {
  size_t i;
  for (i = 0; s[i] != '\0'; i++) {
    for (size_t j = 0; charset[j] != '\0'; j++) {
      if (s[i] == charset[j]) return i;
    }
  }
  return i;
}
