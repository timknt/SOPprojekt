#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "output.h"

void search(const char *text, const char *searchText, Node **head, char *fileName) {
    if (!text || !searchText || !head) {
        return;
    }

    int line = 1;
    const char *currentLine = text;
    const char *match;

    while (currentLine) {
        const char *lineEnd = strchr(currentLine, '\n');
        size_t lineLength = lineEnd ? (size_t)(lineEnd - currentLine) : strlen(currentLine);

        char *lineCopy = (char *)malloc(lineLength + 1);
        if (!lineCopy) {
            writeError("Memory allocation failed");
            return;
        }

        strncpy(lineCopy, currentLine, lineLength);
        lineCopy[lineLength] = '\0';

        match = strstr(lineCopy, searchText);
        while (match) {
            Data result;
            result.text = strdup(lineCopy);
            if (!result.text) {
                free(lineCopy);
                return;
            }
            result.line = line;
            result.startPosition = (int)(match - lineCopy);
            result.fileName = fileName;

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
