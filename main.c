#include <stdio.h>
#include <dirent.h>
#include<pthread.h>
#include <string.h>

#include "greppy_args.h"
#include "recursive.h"
#include "output.h"
#include "readFile.h"
#include "thread.h"

int main(int argc, char *argv[]) {
    GrepOptions options = {0};

    parse_arguments(argc, argv, &options);
    validate_arguments(&options);

    int capacity = 1;

    File *fileList = malloc(capacity * sizeof(File));
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

    if (options.file_or_dir && !options.from_stdin) {
        writeOutput("Searching in: %s\n", options.file_or_dir);
    }

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

        ThreadData threadData[recursiveFileCount];

        for (int i = 0; i <= recursiveFileCount; i++) {
           threadData[i].file = &fileList[i];
            threadData[i].results = NULL;
            threadData[i].searchText = strdup(options.search_text);
        }

        for (int i = 0; i <= recursiveFileCount; i++) {
            pthread_create(&threads[i], NULL, greppyThread, &threadData[i]);
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
