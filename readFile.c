#include "readFile.h"

#include "caseInsensitive.h"

long getFileSize(FILE *file) {
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);
    return filesize;
}

char *readFile(char *filename, bool case_insensitive) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "File could not be opened\n");
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

int testReadFile() {
    const char *filename = "Testing/test.txt";

    char *content = readFile((char *)filename, false);

    printf("Dateiinhalt:\n%s\n", content);

    free(content);
    return EXIT_SUCCESS;
}