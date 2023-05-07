#include <stdatomic.h>

#ifdef atomic_thread_fence
#undef atomic_thread_fence
#endif

void atomic_thread_fence(memory_order ord) {
#if __clang__
    __c11_atomic_thread_fence(ord);
#else
#error unknown compiler
#endif
}

#ifdef atomic_signal_fence
#undef atomic_signal_fence
#endif

void atomic_signal_fence(memory_order ord) {
#if __clang__
    __c11_atomic_signal_fence(ord);
#else
#error unknown compiler
#endif

}
