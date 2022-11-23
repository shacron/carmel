// MIT License

// Copyright (c) 2022 Shac Ron

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// SPDX-License-Identifier: MIT License

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
