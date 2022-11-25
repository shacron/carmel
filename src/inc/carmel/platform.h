#pragma once

// The linking target must provide a version of these platform functions.

// Write a single character to the to output stream
void platform_putchar(char c);
// Read a single character from the output stream
int platform_getchar(void);

// Exit the current execution
_Noreturn void platform_abort(int status);
