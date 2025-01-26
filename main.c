#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "greppy_args.h"
#include "readFile.h"

int main(int argc, char *argv[]) {
    GrepOptions options = {0};

    parse_arguments(argc, argv, &options);
    validate_arguments(&options);

    if (options.quiet) {
        printf("Quiet mode enabled. No output will be displayed.\n");
    }

    if (options.recursive) {
        printf("Recursive search enabled.\n");
    }

    if (options.case_insensitive) {
        printf("Case-insensitive search enabled.\n");
    }

    if (options.count) {
        printf("Match count will be displayed instead of matches.\n");
    }

    if (options.max_count_set) {
        printf("Maximum number of matches to display: %d\n", options.max_count);
    }

    if (options.from_stdin) {
        printf("Reading input from stdin. Enter text:\n");
    }

    if (options.search_text) {
        printf("Searching for: %s\n", options.search_text);
    }

    if (options.file_or_dir) {
        printf("Searching in: %s\n", options.file_or_dir);
    } else {
        printf("No file or directory specified. Defaulting to stdin.\n");
    }

    printf("Arguments processed successfully. Ready to perform the search.\n");


    char *filename;
    if (options.from_stdin) {
        filename = "/dev/stdin";
    } else {
        filename = options.file_or_dir;
    }

    char *content = readFile(filename);
    if (content == NULL) {
        fprintf(stderr, "Fehler beim Lesen der Datei\n");
        return EXIT_FAILURE;
    }

    printf("Dateiinhalt:\n%s\n", content);

    free(content);

    return 0;
}
