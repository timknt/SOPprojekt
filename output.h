#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdarg.h>
#include <_stdio.h>

void writeError(const char* format, ...);
void writeOutput(const char* format, ...);

#endif //OUTPUT_H
