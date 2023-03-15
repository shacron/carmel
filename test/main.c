#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int test_qsort(void);
int test_strcmp(void);

unsigned int global_seed;

int main(int argc, char *argv[]) {
    global_seed = time(NULL);
    printf("seed = %#x\n", global_seed);

    test_strcmp();
    test_qsort();
    return 0;
}

