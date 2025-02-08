#include <stdio.h>
#include <string.h>
#include "linkedList.h"

void search(char *text, const char *searchText, Node **head) {
    int line = 1;
    char *currentLine = text;
    char *match;

    while (currentLine) {
        match = strstr(currentLine, searchText);
        while (match) {
            Data result;
            result.text = currentLine;
            result.line = line;
            result.startPosition = (int)(match - currentLine);

            insertAtTail(head, result);

            match = strstr(match + 1, searchText);
        }

        currentLine = strchr(currentLine, '\n');
        if (currentLine) {
            currentLine++;
            line++;
        }
    }
}
