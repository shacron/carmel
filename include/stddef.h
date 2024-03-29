#pragma once

#define NULL ((void *)0)

#ifdef __SIZE_TYPE__
typedef __SIZE_TYPE__ size_t;
#else
// This may be incorrect for some targets
typedef unsigned long size_t;
#endif

#ifdef __PTRDIFF_TYPE__
typedef __PTRDIFF_TYPE__ ptrdiff_t;
#else
typedef unsigned long ptrdiff_t;
#endif

#ifdef __BIGGEST_ALIGNMENT__
typedef struct { int x; } max_align_t __attribute__((aligned(__BIGGEST_ALIGNMENT__)));
#else
typedef unsigned long long max_align_t;
#endif

#define offsetof(t,m) __builtin_offsetof(t,m)
