#pragma once

#include <stdlib.h>
#include <stdio.h>

#define static_assert _Static_assert

#ifdef NDEBUG
#define assert(expr) do {} while(0)
#else
#define assert(expr) \
    do { if (!(expr)) { printf("%s:%u: assertion failed: '" #expr "'\n", __FUNCTION__, __LINE__); abort(); } } while(0)
#endif // NDEBUG
