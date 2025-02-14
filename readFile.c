#include "readFile.h"
#include <stdbool.h>

#include "caseInsensitive.h"

long getFileSize(FILE *file) {
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);
    return filesize;
}

char *readFile(char *filename, bool case_insensitive) {
    FILE *file = fopen(filename, "r+");
    if (file == NULL) {
        return NULL;
    }
    long fileSize = getFileSize(file);

    char *buffer = malloc(fileSize + 1);

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    buffer[bytesRead] = '\0';
    fclose(file);

    if (case_insensitive) {
        caseInsensitive(buffer);
    }

    return buffer;
}

char *readStdin(bool case_insensitive) {
    int size = 4;
    int charCount = 0;
    char *buffer = malloc(size);
    int data;
    while ((data = fgetc(stdin)) != EOF) { // Read the data from input
        if (charCount >= size) {
            size = 2 * size;
            buffer = (char *)realloc(buffer, size);
        }
        buffer[charCount++] = (char)data;
    }
    if (case_insensitive) {
        caseInsensitive(buffer);
    }

    return buffer;
}

int testReadFile() {
    const char *filename = "Testing/test.txt";

    char *content = readFile((char *)filename, false);

    printf("Dateiinhalt:\n%s\n", content);

    free(content);
    return EXIT_SUCCESS;
}