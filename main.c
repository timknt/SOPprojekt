#include <stdio.h>
#include <dirent.h>
#include<pthread.h>
#include <string.h>

#include "greppy_args.h"
#include "recursive.h"
#include "output.h"
#include "readFile.h"

void *readFileContent(void *arg) {
    File *file = (File*)arg;

    char *content = readFile(file->fileName);

    if (content == NULL) {
        pthread_exit(NULL);
    }
    strcpy(file->content, content);
    free(content);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    GrepOptions options = {0};

    parse_arguments(argc, argv, &options);
    validate_arguments(&options);

    int capacity = 1;

    File *fileList = malloc(1 * sizeof(File));
    int recursiveFileCount = 0;

    if (options.quiet) {
        writeOutput("Quiet mode enabled. No output will be displayed.\n");
    }

    if (options.recursive) {
        printf("Recursive search enabled.\n");
        recursiveFileCount = getFilesInDir(&fileList, options.file_or_dir, recursiveFileCount, capacity);
    }

    if (options.case_insensitive) {
        writeOutput("Case-insensitive search enabled.\n");
    }

    if (options.count) {
        writeOutput("Match count will be displayed instead of matches.\n");
    }

    if (options.max_count_set) {
        writeOutput("Maximum number of matches to display: %d\n", options.max_count);
    }

    if (options.from_stdin) {
        writeOutput("Reading input from stdin. Enter text:\n");
    }

    if (options.search_text) {
        writeOutput("Searching for: %s\n", options.search_text);
    }

    if (options.file_or_dir) {
        writeOutput("Searching in: %s\n", options.file_or_dir);
    } else {
        writeOutput("No file or directory specified. Defaulting to stdin.\n");
    }

    writeOutput("Arguments processed successfully. Ready to perform the search.\n");


    char *filename;
    if (options.from_stdin) {
        filename = "/dev/stdin";
    } else {
        filename = options.file_or_dir;
    }

    if (recursiveFileCount == 0 || fileList == NULL) {
        char *content = readFile(filename);

        writeOutput("Dateiinhalt:\n%s\n", content);
        free(content);
    } else {
        writeOutput("FileInfo\n");

        pthread_t threads[recursiveFileCount];

        for (int i = 0; i <= recursiveFileCount; i++) {
            pthread_create(&threads[i], NULL, readFileContent, &fileList[i]);
        }
        for (int i = 0; i <= recursiveFileCount; i++) {
            pthread_join(threads[i], NULL);
        }

        for (int i = 0; i <= recursiveFileCount; i++) {
            printf("NAME: %s CONTENT: %s \n", fileList[i].fileName, fileList[i].content);
        }

    }
    free(fileList);

    return 0;
}
