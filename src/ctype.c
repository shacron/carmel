// SPDX-License-Identifier: MIT License
// Copyright (c) 2022 Shac Ron

#include <ctype.h>

int digittoint(int c) {
    if ((c >= '0') && (c <= '9')) return c - '0';
    if ((c >= 'A') && (c <= 'F')) return c - 'A' + 10;
    if ((c >= 'a') && (c <= 'f')) return c - 'a' + 10;
    return 0;
}

int isalnum(int c) {
    if ((c >= '0') && (c <= '9')) return 1;
    if ((c >= 'A') && (c <= 'Z')) return 1;
    if ((c >= 'a') && (c <= 'z')) return 1;
    return 0;
}

int isalpha(int c) {
    if ((c >= 'A') && (c <= 'Z')) return 1;
    if ((c >= 'a') && (c <= 'z')) return 1;
    return 0;
}

int isrune(int c) {
    return isascii(c);
}

int isascii(int c) {
    return ((unsigned int)c <= 0177);
}

int iscntrl(int c) {
    unsigned int u = c;
    if (u <= 007) return 1;
    if ((u >= 010) && (u <= 017)) return 1;
    if ((u >= 020) && (u <= 037)) return 1;
    return (u == 0177);
}

int isnumber(int c) {
    return isdigit(c);
}
int isdigit(int c) {
    return ((c >= '0') && (c <= '9'));
}

int isgraph(int c) {
    return ((c >= 041) && (c <= 0176));
}

int ishexnumber(int c) {
    return isxdigit(c);
}

int isxdigit(int c) {
    if ((c >= '0') && (c <= '9')) return 1;
    if ((c >= 'A') && (c <= 'F')) return 1;
    if ((c >= 'a') && (c <= 'f')) return 1;
    return 0;
}

int islower(int c) {
    return ((c >= 'a') && (c <= 'z'));
}

int isprint(int c) {
    return ((c >= 040) && (c <= 0176));
}

int ispunct(int c) {
    if ((c >= 041) && (c <= 057)) return 1;
    if ((c >= 072) && (c <= 0100)) return 1;
    if ((c >= 0133) && (c <= 0140)) return 1;
    if ((c >= 0173) && (c <= 0176)) return 1;
    return 0;
}

int isspace(int c) {
    return ((c == ' ') || (c == '\t') || (c == '\n') ||
            (c == '\v') || (c == '\f') || (c == '\r'));
}

int isupper(int c) {
    return ((c >= 'A') && (c <= 'Z'));
}

int toascii(int c) {
    return ((unsigned int)c) & 0x7f;
}

int tolower(int c) {
    if ((c >= 'A') && (c <= 'Z')) return (c - 'A' + 'a');
    return c;
}

int toupper(int c) {
    if ((c >= 'a') && (c <= 'z')) return (c - 'a' + 'A');
    return c;
}
