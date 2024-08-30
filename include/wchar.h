#pragma once

// This file is supposed redundantly declare
// NULL, WCHAR_MIN/MAX, and size_t.
// Only WCHAR_MIN and MAX have been duplicated here.
// WINT_MIN/MAX are (insanely) defined in stdint.h.

#if __clang__

typedef __WCHAR_TYPE__ wchar_t;
typedef __WINT_TYPE__  wint_t;

#define WCHAR_MAX __WCHAR_MAX__
#define WEOF      (wint_t)-1

#else // clang

#error unknown compiler

#define WCHAR_MIN (wchar_t)(WCHAR_MAX + 1)

#endif
