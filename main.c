#include <stdio.h>
#include <dirent.h>
#include<pthread.h>
#include <string.h>

#include "caseInsensitive.h"
#include "greppy_args.h"
#include "recursive.h"
#include "output.h"
#include "readFile.h"
#include "linkedList.h"
#include "search.h"
#include "count.h"
#include "thread.h"


void checkOptions(GrepOptions options) {
    if (options.quiet) {
        writeOutput("Quiet mode enabled. No output will be displayed.\n");
    }

    if (options.recursive) {
        writeOutput("Recursive search enabled.\n");
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
}

int main(int argc, char *argv[]) {
    GrepOptions options = {0};

    parse_arguments(argc, argv, &options);
    validate_arguments(&options);

    checkOptions(options);

    if (options.from_stdin) {
        options.from_stdin = "/dev/stdin";
    }
    if (options.case_insensitive) {
        caseInsensitive(options.search_text);
    }

    Node *head = NULL;
    char *content = NULL;

    int capacity = 1;

    File *fileList = malloc(capacity * sizeof(File));
    int recursiveFileCount = 0;

    if (options.recursive) {
        recursiveFileCount = getFilesInDir(&fileList, options.file_or_dir, recursiveFileCount, capacity);
        pthread_t threads[recursiveFileCount];

        ThreadData threadData[recursiveFileCount];

        for (int i = 0; i <= recursiveFileCount; i++) {
            Node *head = NULL;
            threadData[i].file = &fileList[i];
            threadData[i].results = head;
            threadData[i].searchText = strdup(options.search_text);
            threadData[i].case_insensitive = options.case_insensitive;
        }

        for (int i = 0; i < recursiveFileCount; i++) {
            pthread_create(&threads[i], NULL, greppyThread, &threadData[i]);
        }
        for (int i = 0; i < recursiveFileCount; i++) {
            pthread_join(threads[i], NULL);
        }

        for (int i = 0; i < recursiveFileCount; i++) {
            concatenateLists(&head, &threadData[i].results);
        }
    }
    else {
        free(fileList);
        content = readFile(options.file_or_dir, options.case_insensitive);
        if (content == NULL) {
            writeError("Error reading file\n");
            free(content);
            freeList(&head);
            return EXIT_FAILURE;
        }

        search(content, options.search_text, &head);
    }

    if (head == NULL) writeError("Error searching fileContent\n");

    int matchCount = count(&head);

    if (options.quiet) {
        if (matchCount > 0) {
            free(content);
            freeList(&head);
            return EXIT_SUCCESS;
        }
        free(content);
        freeList(&head);
        return EXIT_FAILURE;
    }

    if (options.count&&!options.max_count_set) {
        writeOutput("Total count of matches: %d\n", matchCount);
        free(content);
        freeList(&head);
        return EXIT_SUCCESS;
    }

    if (options.count&&options.max_count_set) {
        if (matchCount > options.max_count_set) {
            writeOutput("Total count of matches found until limit: %d\n", options.max_count);
        }
        else {
            writeOutput("Total count of matches until: %d\n", matchCount);
        }
        free(content);
        freeList(&head);
        return EXIT_SUCCESS;
    }


    printResult(head, options.max_count_set, options.max_count, options.search_text);

    free(content);
    freeList(&head);

    return 0;
}
