#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "greppy_args.h"

void print_usage(const char *prog_name) {
    printf("Usage: %s [options] \"search_text\" [file/dir]\n", prog_name);
    printf("Options:\n");
    printf("  -q            Quiet mode, no output, only exit code\n");
    printf("  -m NUM        Maximum number of matches to output\n");
    printf("  -c            Output the count of matches\n");
    printf("  -r            Search recursively in directories\n");
    printf("  -i            Case-insensitive search\n");
    printf("  \"-\"          Read input from stdin\n");
    printf("  \"search_text\" Text to search for (required)\n");
    printf("  [file/dir]    File or directory to search in (optional)\n");
}

void parse_arguments(int argc, char *argv[], GrepOptions *options) {
    int opt;
    int positional_args = 0;

    while ((opt = getopt(argc, argv, "qm:cri")) != -1) {
        switch (opt) {
            case 'q':
                options->quiet = true;
            break;
            case 'm':
                options->max_count_set = true;
            options->max_count = atoi(optarg);
            break;
            case 'c':
                options->count = true;
            break;
            case 'r':
                options->recursive = true;
            break;
            case 'i':
                options->case_insensitive = true;
            break;
            default:
                print_usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = optind; i < argc; i++) {
        if (positional_args == 0) {
            options->search_text = argv[i];
            positional_args++;
        } else if (positional_args == 1) {
            options->file_or_dir = argv[i];
            positional_args++;
        } else {
            fprintf(stderr, "Error: Too many arguments provided. Only 'search_text' and an optional 'file_or_dir' are allowed.\n");
            exit(EXIT_FAILURE);
        }
    }

    if (options->search_text == NULL) {
        fprintf(stderr, "Error: search_text is required.\n");
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (options->recursive && positional_args < 2) {
        fprintf(stderr, "Error: Recursive search (-r) requires both 'search_text' and a file/directory.\n");
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }
}

void validate_arguments(GrepOptions *options) {
    if (options->search_text == NULL) {
        fprintf(stderr, "Error: search_text is required.\n");
        exit(EXIT_FAILURE);
    }

    if (options->from_stdin) {
        printf("Reading from stdin. Please provide input:\n");
    }
}
