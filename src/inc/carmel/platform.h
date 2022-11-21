#pragma once

// The linking target must provide a version of these platform functions.

// Write a single character to the to output stream
void platform_putchar(char c);

// Exit the current execution
_Noreturn void platform_abort(void);
