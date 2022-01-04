#include <string.h>

char *strpbrk(const char *s, const char *charset) {
  for ( ; *s; s++) {
    for (size_t j = 0; charset[j] != '\0'; j++) {
      if (*s == charset[j]) return (char*)s;
    }
  }
  return NULL;
}
