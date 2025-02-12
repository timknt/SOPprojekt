#include <stdio.h>

#include "caseInsensitive.h"
#include "greppy_args.h"
#include "output.h"
#include "readFile.h"
#include "linkedList.h"
#include "search.h"

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

    if (options.recursive) {
        //recursive(head, options.file_or_dir, options.search_text, options.case_insensitive)
    }
    else {
        content = readFile(options.file_or_dir, options.case_insensitive);
        if (content == NULL) {
            writeError("Error reading file\n");
            return EXIT_FAILURE;
        }

        search(content, options.search_text, &head);
    }

    if (head == NULL) writeError("Error searching fileContent\n");

    int matchCount = getLength(head);

    if (options.quiet) {
        if (matchCount > 0) {
            return EXIT_SUCCESS;
        }
        return EXIT_FAILURE;
    }

    if (options.count&&!options.max_count_set) {
        writeOutput("Total count of matches: %d\n", matchCount);
        return EXIT_SUCCESS;
    }

    if (options.count&&options.max_count_set) {
        if (matchCount > options.max_count_set) {
            writeOutput("Total count of matches found until limit: %d\n", options.max_count);
        }
        else {
            writeOutput("Total count of matches until: %d\n", matchCount);
        }
        return EXIT_SUCCESS;
    }

    //printResult(head, options.max_count_set, options.max_count)

    free(content);
    freeList(&head);

    return 0;
}
