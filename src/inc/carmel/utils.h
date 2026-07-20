// SPDX-License-Identifier: MIT License
// Copyright (c) 2026 Shac Ron

#pragma once

#include <stdbool.h>

#if __clang__ || __GNUC__

static inline bool carmel_add_overflow_ulong(unsigned long a, unsigned long b, unsigned long *result) {
    return __builtin_uaddl_overflow(a, b, result);
}

static inline bool carmel_mul_overflow_ulong(unsigned long a, unsigned long b, unsigned long *result) {
    return __builtin_umull_overflow(a, b, result);
}

#else

// todo: implement these

#endif
