#include <string.h>

char *strtok_r(char *restrict s, const char *restrict sep, char **restrict lasts) {
  if (s == NULL) {
    s = *lasts;
    if (s == NULL) return NULL;
  }

  int found = 0;
  for (char *p = s; *p; p++) {
    for (int i = 0; sep[i] != '\0'; i++) {
      if (*p == sep[i]) {
        *p = '\0';
        found = 1;
        goto outer_continue;
      }
    }
    if (found) {
      *lasts = p;
      return s;
    }
outer_continue:
    (void)0;
  }

  *lasts = NULL;
  return s;
}

