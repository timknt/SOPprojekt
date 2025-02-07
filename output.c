//
// Created by Adrian Stelter on 31.01.25.
//

#include <stdarg.h>
#include <stdio.h>

void writeError(const char* format, ...) {
    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}

void writeOutput(const char* format, ...) {
    va_list args;
    va_start(args, format);

    vprintf(format, args);

    va_end(args);
}