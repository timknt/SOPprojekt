#include "readFile.h"

long getFileSize(FILE *file) {
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);
    return filesize;
}

char *readFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    long fileSize = getFileSize(file);

    char *buffer = malloc(fileSize + 1);

    size_t bytesRead = fread(buffer, 1, fileSize, file);

    buffer[bytesRead] = '\0';
    fclose(file);
    return buffer;
}

int testReadFile() {
    const char *filename = "Testing/test.txt";

    char *content = readFile((char *)filename);
    if (content == NULL) {
        fprintf(stderr, "Fehler beim Lesen der Datei\n");
        return EXIT_FAILURE;
    }

    printf("Dateiinhalt:\n%s\n", content);

    free(content);
    return EXIT_SUCCESS;
}