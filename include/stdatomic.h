#pragma once

#include <stddef.h>
#include <stdint.h>

#if __clang__

#define ATOMIC_BOOL_LOCK_FREE       __CLANG_ATOMIC_BOOL_LOCK_FREE
#define ATOMIC_CHAR_LOCK_FREE       __CLANG_ATOMIC_CHAR_LOCK_FREE
#define ATOMIC_CHAR16_T_LOCK_FREE   __CLANG_ATOMIC_CHAR16_T_LOCK_FREE
#define ATOMIC_CHAR32_T_LOCK_FREE   __CLANG_ATOMIC_CHAR32_T_LOCK_FREE
#define ATOMIC_WCHAR_T_LOCK_FREE    __CLANG_ATOMIC_WCHAR_T_LOCK_FREE
#define ATOMIC_SHORT_LOCK_FREE      __CLANG_ATOMIC_SHORT_LOCK_FREE
#define ATOMIC_INT_LOCK_FREE        __CLANG_ATOMIC_INT_LOCK_FREE
#define ATOMIC_LONG_LOCK_FREE       __CLANG_ATOMIC_LONG_LOCK_FREE
#define ATOMIC_LLONG_LOCK_FREE      __CLANG_ATOMIC_LLONG_LOCK_FREE
#define ATOMIC_POINTER_LOCK_FREE    __CLANG_ATOMIC_POINTER_LOCK_FREE

typedef enum memory_order {
    memory_order_relaxed = __ATOMIC_RELAXED,
    memory_order_consume = __ATOMIC_CONSUME,
    memory_order_acquire = __ATOMIC_ACQUIRE,
    memory_order_release = __ATOMIC_RELEASE,
    memory_order_acq_rel = __ATOMIC_ACQ_REL,
    memory_order_seq_cst = __ATOMIC_SEQ_CST
} memory_order;

#else
#error unknown compiler
#endif  // __clang__

typedef _Atomic(_Bool)              atomic_bool;
typedef _Atomic(char)               atomic_char;
typedef _Atomic(signed char)        atomic_schar;
typedef _Atomic(unsigned char)      atomic_uchar;
typedef _Atomic(short)              atomic_short;
typedef _Atomic(unsigned short)     atomic_ushort;
typedef _Atomic(int)                atomic_int;
typedef _Atomic(unsigned int)       atomic_uint;
typedef _Atomic(long)               atomic_long;
typedef _Atomic(unsigned long)      atomic_ulong;
typedef _Atomic(long long)          atomic_llong;
typedef _Atomic(unsigned long long) atomic_ullong;
typedef _Atomic(uint_least16_t)     atomic_char16_t;
typedef _Atomic(uint_least32_t)     atomic_char32_t;
typedef _Atomic(int_least8_t)       atomic_int_least8_t;
typedef _Atomic(uint_least8_t)      atomic_uint_least8_t;
typedef _Atomic(int_least16_t)      atomic_int_least16_t;
typedef _Atomic(uint_least16_t)     atomic_uint_least16_t;
typedef _Atomic(int_least32_t)      atomic_int_least32_t;
typedef _Atomic(uint_least32_t)     atomic_uint_least32_t;
typedef _Atomic(int_least64_t)      atomic_int_least64_t;
typedef _Atomic(uint_least64_t)     atomic_uint_least64_t;
typedef _Atomic(int_fast8_t)        atomic_int_fast8_t;
typedef _Atomic(uint_fast8_t)       atomic_uint_fast8_t;
typedef _Atomic(int_fast16_t)       atomic_int_fast16_t;
typedef _Atomic(uint_fast16_t)      atomic_uint_fast16_t;
typedef _Atomic(int_fast32_t)       atomic_int_fast32_t;
typedef _Atomic(uint_fast32_t)      atomic_uint_fast32_t;
typedef _Atomic(int_fast64_t)       atomic_int_fast64_t;
typedef _Atomic(uint_fast64_t)      atomic_uint_fast64_t;
typedef _Atomic(intptr_t)           atomic_intptr_t;
typedef _Atomic(uintptr_t)          atomic_uintptr_t;
typedef _Atomic(size_t)             atomic_size_t;
typedef _Atomic(ptrdiff_t)          atomic_ptrdiff_t;
typedef _Atomic(intmax_t)           atomic_intmax_t;
typedef _Atomic(uintmax_t)          atomic_uintmax_t;

typedef struct atomic_flag {
    atomic_bool value;
} atomic_flag;

void atomic_thread_fence(memory_order ord);
void atomic_signal_fence(memory_order ord);

#if __clang__
#define atomic_init                             __c11_atomic_init
#define atomic_thread_fence(ord)                __c11_atomic_thread_fence(ord)
#define atomic_signal_fence(ord)                __c11_atomic_signal_fence(ord)
#define atomic_is_lock_free(obj)                __c11_atomic_is_lock_free(sizeof(*(obj)))
#define atomic_store(obj, v)                    __c11_atomic_store(obj, v, __ATOMIC_SEQ_CST)
#define atomic_store_explicit(obj, v, o)        __c11_atomic_store(obj, v, o)
#define atomic_load(obj)                        __c11_atomic_load(obj, __ATOMIC_SEQ_CST)
#define atomic_load_explicit(obj, o)            __c11_atomic_load(obj, o)
#define atomic_fetch_add(obj, v)                __c11_atomic_fetch_add(obj, v, __ATOMIC_SEQ_CST)
#define atomic_fetch_add_explicit(obj, v, o)    __c11_atomic_fetch_add(obj, v, o)
#define atomic_fetch_sub(obj, v)                __c11_atomic_fetch_sub(obj, v, __ATOMIC_SEQ_CST)
#define atomic_fetch_sub_explicit(obj, v, o)    __c11_atomic_fetch_sub(obj, v, o)
#define atomic_fetch_and(obj, v)                __c11_atomic_fetch_and(obj, v, __ATOMIC_SEQ_CST)
#define atomic_fetch_and_explicit(obj, v, o)    __c11_atomic_fetch_and(obj, v, o)
#define atomic_fetch_or(obj, v)                 __c11_atomic_fetch_or(obj, v, __ATOMIC_SEQ_CST)
#define atomic_fetch_or_explicit(obj, v, o)     __c11_atomic_fetch_or(obj, v, o)
#define atomic_fetch_xor(obj, v)                __c11_atomic_fetch_xor(obj, v, __ATOMIC_SEQ_CST)
#define atomic_fetch_xor_explicit(obj, v, o)    __c11_atomic_fetch_xor(obj, v, o)
#define atomic_exchange(obj, desired)               __c11_atomic_exchange(obj, desired, __ATOMIC_SEQ_CST)
#define atomic_exchange_explicit(obj, desired, o)   __c11_atomic_exchange(obj, desired, o)
#define atomic_compare_exchange_strong(obj, expected, desired) \
            __c11_atomic_compare_exchange_strong(obj, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_compare_exchange_strong_explicit(obj, expected, desired, o, o_fail) \
            __c11_atomic_compare_exchange_strong(obj, expected, desired, o, o_fail)
#define atomic_compare_exchange_weak(obj, expected, desired) \
            __c11_atomic_compare_exchange_weak(obj, expected, desired, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define atomic_compare_exchange_weak_explicit(obj, expected, desired, o, o_fail) \
            __c11_atomic_compare_exchange_weak(obj, expected, desired, o, o_fail)


#endif  // __clang__

