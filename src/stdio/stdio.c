// SPDX-License-Identifier: MIT License
// Copyright (c) 2022 Shac Ron

#include <errno.h>
#include <stdio.h>
#include <string.h>

void perror(const char *s) {
    // this should go to stderr, which is not yet supported
    printf("%s: %s\n", s, strerror(errno));
}
