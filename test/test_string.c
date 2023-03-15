#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool comp_equal(int a, int b);

#define countof(p) (sizeof(p) / sizeof(p[0]))
#define assert_comp(f, a, b) assert(comp_equal(f(a,b),carmel_ ## f(a,b)))

int carmel_strcmp(const char *s1, const char *s2);

bool comp_equal(int a, int b) {
    if (a == 0) return (b == 0);
    if (a < 0) return (b < 0);
    return (b > 0);
}

int test_strcmp(void) {
    // pairs of strings to compare
    static const char * strings[] = {
        "a", "a",
        "a", "aa",
        "aa", "a",
        "aa", "aa",
        "", "",
        "", "a",
        "a", "",
    };

    for (int i = 0; i < countof(strings); i += 2) {
        printf("comparing %s, %s\n", strings[i], strings[i+1]);
        assert_comp(strcmp, strings[i], strings[i+1]);
    }
    return 0;
}
