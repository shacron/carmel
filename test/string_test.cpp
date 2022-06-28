#include <gtest/gtest.h>
#include <memory>
#include <stdint.h>
#include <string.h>

#define countof(p)           (sizeof(p) / sizeof(p[0]))

namespace carmel {

#define restrict

extern "C" {
void *carmel_memccpy(void *restrict dst, const void *restrict src, int c, size_t n);
void *carmel_memchr(const void *s, int c, size_t n);
int carmel_memcmp(const void *s1, const void *s2, size_t n);
void *carmel_memcpy(void *restrict dst, const void *restrict src, size_t n);
void *carmel_memmove(void *dst, const void *src, size_t len);
void *carmel_memset(void *b, int c, size_t len);
char *carmel_strcat(char *restrict s1, const char *restrict s2);
char *carmel_strchr(const char *s, int c);
int carmel_strcmp(const char *s1, const char *s2);
int carmel_strcoll(const char *s1, const char *s2);
char *carmel_strcpy(char *dst, const char * src);
size_t carmel_strcspn(const char *s, const char *charset);
char *carmel_strdup(const char *s);
char *carmel_strerror(int errnum);
char *carmel_strncat(char *restrict s1, const char *restrict s2, size_t n);
char *carmel_strncpy(char *dst, const char *src, size_t len);
size_t carmel_strlen(const char *s);
int carmel_strncmp(const char *s1, const char *s2, size_t n);
char *carmel_strpbrk(const char *s, const char *charset);
char *carmel_strrchr(const char *s, int c);
size_t carmel_strspn(const char *s, const char *charset);
char *carmel_strstr(const char *haystack, const char *needle);
}

class StringTest: public ::testing::Test {
protected:

};

TEST_F(StringTest, memcmp) {
  const uint8_t comps1[] = {
    0x0,
    0x1,
    0xfe,
    0xff,
  };

  for (int i = 0; i < countof(comps1); i++) {
    for (int j = 0; j < countof(comps1); j++) {
      int p = memcmp(&comps1[i], &comps1[j], 1);
      int q = carmel_memcmp(&comps1[i], &comps1[j], 1);
      ASSERT_EQ(p, q);
    }
  }

  const uint8_t comps2[][2] = {
    { 0x10, 0x20 },
    { 0x10, 0x25 },
    { 0x10, 0x27 },

    { 0x13, 0x20 },
    { 0x13, 0x25 },
    { 0x13, 0x27 },

    { 0x18, 0x20 },
    { 0x18, 0x25 },
    { 0x18, 0x27 },
  };

  for (int i = 0; i < countof(comps2); i++) {
    for (int j = 0; j < countof(comps2); j++) {
      int p = memcmp(comps2[i], comps2[j], 2);
      int q = carmel_memcmp(comps2[i], comps2[j], 2);
      ASSERT_TRUE(p < 0 ? (q < 0) : p == 0 ? q == 0 : q > 0);
    }
  }
}



TEST_F(StringTest, memchr) {
  const void *p, *q;

  const char *haystack = "abcdef";
  p = memchr(haystack, 'a', 6);
  q = carmel_memchr(haystack, 'a', 6);
  ASSERT_EQ(p, q);
}


} // namespace carmel
