#include <stdlib.h>

#include <carmel/platform.h>

_Noreturn void abort(void) {
    platform_abort();
}
