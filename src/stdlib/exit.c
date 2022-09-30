#include <stdlib.h>

extern _Noreturn void platform_abort(void);

_Noreturn void abort(void) {
    platform_abort();
}
