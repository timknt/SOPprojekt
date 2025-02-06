#include <stdio.h>

#include "greppy_args.h"
#include "output.h"
#include "readFile.h"

int main(int argc, char *argv[]) {
    GrepOptions options = {0};

    parse_arguments(argc, argv, &options);
    validate_arguments(&options);

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
        writeOutput("Matchcount will be displayed instead of matches.\n");
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

    char *content = readFile(filename);
    if (content == NULL) {
        writeError("Fehler beim Lesen der Datei\n");
        return EXIT_FAILURE;
    }

    writeOutput("Dateiinhalt:\n%s\n", content);

    free(content);

    return 0;
}
