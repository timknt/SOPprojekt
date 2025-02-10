#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

void search(const char *text, const char *searchText, Node **head) {
    int line = 1;
    const char *currentLine = text;
    const char *match;

    while (currentLine) {
        const char *lineEnd = strchr(currentLine, '\n');
        size_t lineLength = lineEnd ? (size_t)(lineEnd - currentLine) : strlen(currentLine);

        char *lineCopy = (char *)malloc(lineLength + 1);
        if (!lineCopy) {
            perror("Memory allocation failed");
            return;
        }
        strncpy(lineCopy, currentLine, lineLength);
        lineCopy[lineLength] = '\0';

        match = strstr(lineCopy, searchText);
        while (match) {
            Data result;
            result.text = strdup(lineCopy);
            result.line = line;
            result.startPosition = (int)(match - lineCopy);

            insertAtTail(head, result);

            match = strstr(match + 1, searchText);
        }

        free(lineCopy);

        if (lineEnd) {
            currentLine = lineEnd + 1;
            line++;
        } else {
            break;
        }
    }
}
