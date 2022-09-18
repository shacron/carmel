#pragma once

#if __clang__

#define CHAR_BIT      __CHAR_BIT__

// todo
// #define CHAR_MIN
// #define CHAR_MAX
// #define BOOL_WIDTH

#define SCHAR_MAX     __SCHAR_MAX__
#define SHRT_MAX      __SHRT_MAX__
#define INT_MAX       __INT_MAX__
#define LONG_MAX      __LONG_MAX__
#define LLONG_MAX     __LONG_LONG_MAX__
#define PTRDIFF_WIDTH __PTRDIFF_WIDTH__
#define PTRDIFF_MAX   __PTRDIFF_MAX__
#define SIZE_WIDTH    __SIZE_WIDTH__
#define SIZE_MAX      __SIZE_MAX__
#define SIG_ATOMIC_WIDTH __SIG_ATOMIC_WIDTH__
#define SIG_ATOMIC_MAX   __SIG_ATOMIC_MAX__
#define WINT_WIDTH    __WINT_WIDTH__
#define WINT_MAX      __WINT_MAX__
#define WCHAR_WIDTH   __WCHAR_WIDTH__
#define WCHAR_MAX     __WCHAR_MAX__

#else

#error unknown compiler

#endif

#define MB_LEN_MAX    6

#define CHAR_WIDTH    CHAR_BIT
#define SCHAR_WIDTH   CHAR_BIT
#define SHRT_WIDTH    (sizeof(short) * CHAR_BIT)
#define INT_WIDTH     (sizeof(int) * CHAR_BIT)
#define LONG_WIDTH    (sizeof(long) * CHAR_BIT)
#define LLONG_WIDTH   (sizeof(long long) * CHAR_BIT)
#define SCHAR_MIN     (-SCHAR_MAX - 1)
#define SHRT_MIN      (-SHRT_MAX - 1)
#define INT_MIN       (-INT_MAX - 1)
#define LONG_MIN      (-LONG_MAX - 1)
#define LLONG_MIN     (-LLONG_MAX - 1)
#define UCHAR_WIDTH   CHAR_BIT
#define USHRT_WIDTH   (sizeof(unsigned short) * CHAR_BIT)
#define UINT_WIDTH    (sizeof(unsigned int) * CHAR_BIT)
#define ULONG_WIDTH   (sizeof(unsigned long) * CHAR_BIT)
#define ULLONG_WIDTH  (sizeof(unsigned long long) * CHAR_BIT)
#define UCHAR_MAX     ((unsigned char)(~0))
#define USHRT_MAX     ((unsigned short)(~0))
#define UINT_MAX      ((unsigned int)(~0))
#define ULONG_MAX     (~0ul)
#define ULLONG_MAX    (~0ull)
#define PTRDIFF_MIN   (-PTRDIFF_WIDTH - 1)
#define SIG_ATOMIC_MIN (-SIG_ATOMIC_WIDTH - 1)
#define WINT_MIN      (-WINT_MAX - 1)
#define WCHAR_MIN     (-WCHAR_MAX - 1)


