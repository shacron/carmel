#include <stdio.h>
#include <string.h>

int carmel_strcmp(const char *s1, const char *s2);

int test_strcmp(void) {
    int sc = strcmp("hi", "hello");
    int cc = carmel_strcmp("hi", "hello");

    printf("got %d %d\n", sc, cc);
    return 0;
}

int main(int argc, char *argv[]) {
    test_strcmp();
    return 0;
}

