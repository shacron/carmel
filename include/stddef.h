#pragma once

#define NULL ((void *)0)

#ifdef __SIZE_TYPE__
typedef __SIZE_TYPE__ size_t;
#else
// This may be incorrect for some targets
typedef unsigned long size_t;
#endif
