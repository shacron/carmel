#include <gtest/gtest.h>
#include <memory>

namespace carmel {

extern "C" void *carmel_memchr(const void *s, int c, size_t n);

class StringTest: public ::testing::Test {
protected:

};

TEST_F(StringTest, memchr) {
  const void *p, *q;

  const char *haystack = "abcdef";
  p = memchr(haystack, 'a', 6);
  q = carmel_memchr(haystack, 'a', 6);
  ASSERT_EQ(p, q);
}


} // namespace carmel
