#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdarg.h>
#include <stdio.h>
#include "linkedList.h"


void writeError(const char* format, ...);
void writeOutput(const char* format, ...);
void printResult(Node* head, int max_count_set, int max_count, const char* searchText);

#endif //OUTPUT_H
