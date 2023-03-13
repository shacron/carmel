#include <stdio.h>
#include <stdlib.h>

#include <carmel/platform.h>

void platform_putchar(char c) {
    putchar(c);
}

int platform_getchar(void) {
    return getchar();
}

_Noreturn void platform_abort(int status) {
    printf("PLATFORM ABORT\n");
    exit(status);
}
