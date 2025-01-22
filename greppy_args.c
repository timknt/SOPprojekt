#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
            case '?':
                default:
                    print_usage(argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        options->search_text = argv[optind++];
    } else {
        fprintf(stderr, "Error: search_text is required\n");
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    if (optind < argc) {
        options->file_or_dir = argv[optind++];
    } else {
        options->from_stdin = true;
    }
}