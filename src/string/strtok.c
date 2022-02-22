#include <string.h>

char *strtok(char *restrict str, const char *restrict sep) {
  static char *lasts;
  return strtok_r(str, sep, &lasts);
}
