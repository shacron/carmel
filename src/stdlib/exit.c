// SPDX-License-Identifier: MIT License
// Copyright (c) 2022 Shac Ron

#include <stdlib.h>

#include <carmel/platform.h>

void exit(int status) {
    _Exit(status);
}

void _Exit(int status) {
    platform_abort(status);
}

_Noreturn void abort(void) {
    platform_abort(1);
}
