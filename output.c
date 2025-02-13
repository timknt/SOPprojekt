#include "output.h"
#include "linkedList.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
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


void printResult(Node* head, int max_count_set, int max_count, const char* searchText) {
    int count = 0;
    Node* current = head;
    int searchLen = strlen(searchText);

    while (current != NULL) {
        if (max_count_set && count >= max_count) {
            break;
        }

        char* lineText = current->data.text;
        int startPos = current->data.startPosition;

        printf("Line %d, Pos %d: ", current->data.line, startPos);
        printf("%.*s", startPos, lineText);
        printf("\033[1m%.*s\033[0m", searchLen, lineText + startPos);
        printf("%s\n", lineText + startPos + searchLen);

        count++;
        current = current->next;
    }
}