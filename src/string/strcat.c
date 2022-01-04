#include <string.h>

char *strcat(char *restrict s1, const char *restrict s2) {
  char *d = s1;
  while (*d) d++;
  while ((*d++ = *s2++)) ;
  return s1;
}
