#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test.h"

#define BUF_LEN 1024

#define countof(p) (sizeof(p) / sizeof(p[0]))

void carmel_qsort(void *base, size_t num, size_t width, int (*compare)(const void *, const void *));

static int buf_a[BUF_LEN];
static int buf_b[BUF_LEN];

static int comp_int(const void *c0, const void *c1) {
    int a = *(int *)c0;
    int b = *(int *)c1;
    return (a - b);
}

static int qs(const void *base, size_t num) {
    const size_t width = sizeof(int);
    const size_t len = num * width;
    memset(buf_a, 0, BUF_LEN);
    memset(buf_b, 0, BUF_LEN);
    memcpy(buf_a, base, len);
    memcpy(buf_b, base, len);
    qsort(buf_a, num, width, comp_int);
    carmel_qsort(buf_b, num, width, comp_int);
    int result = memcmp(buf_a, buf_b, len);
    // for (size_t i = 0; i < num; i++) {
    //     printf(" %d", buf_a[i]);
    // }
    // printf("\n");
    // for (size_t i = 0; i < num; i++) {
    //     printf(" %d", buf_b[i]);
    // }
    // printf("\n");
    return result;
}

#define ASSERT_QS(a) assert(0 == qs(a, countof(a)))

int test_qsort(void) {

    { const int a[] = { 0 };        ASSERT_QS(a); }
    { const int a[] = { 0, 0 };     ASSERT_QS(a); }
    { const int a[] = { 0, 1 };     ASSERT_QS(a); }
    { const int a[] = { 1, 0 };     ASSERT_QS(a); }
    { const int a[] = { 0, 0, 0 };  ASSERT_QS(a); }
    { const int a[] = { 0, 0, 1 };  ASSERT_QS(a); }
    { const int a[] = { 0, 1, 0 };  ASSERT_QS(a); }
    { const int a[] = { 0, 1, 1 };  ASSERT_QS(a); }
    { const int a[] = { 1, 0, 0 };  ASSERT_QS(a); }
    { const int a[] = { 1, 0, 1 };  ASSERT_QS(a); }
    { const int a[] = { 1, 1, 0 };  ASSERT_QS(a); }
    { const int a[] = { 1, 1, 1 };  ASSERT_QS(a); }
    { const int a[] = { 1, 2, 3 };  ASSERT_QS(a); }
    { const int a[] = { 1, 3, 2 };  ASSERT_QS(a); }
    { const int a[] = { 2, 1, 3 };  ASSERT_QS(a); }
    { const int a[] = { 2, 3, 1 };  ASSERT_QS(a); }
    { const int a[] = { 3, 1, 2 };  ASSERT_QS(a); }
    { const int a[] = { 3, 2, 1 };  ASSERT_QS(a); }
    { const int a[] = { 40, 44, 19, 43 };  ASSERT_QS(a); }
    { const int a[] = { 12, 19, 33, 40, 43, 44, 44, 46, 51, 70, 97 };  ASSERT_QS(a); }
    { const int a[] = { 15, 12, 87, 55, 22, 42, 41, 70, 97, 18, 2, 21 };  ASSERT_QS(a); }

    unsigned int seed = global_seed;

#define ARRAY_LEN 67

    int arr[ARRAY_LEN];
    for (int i = 0; i < 1000; i++) {
        unsigned int len = (rand_r(&seed) % (ARRAY_LEN - 1)) + 1;
        for (unsigned int v = 0; v < len; v++)
            arr[v] = rand_r(&seed) % 100;
        assert(0 == qs(arr, len));
    }

    return 0;
}
