#include "greppy_args.h"

void print_usage() {
    writeOutput("Usage: greppy [options] \"search_text\" [file/dir]\n");
    writeOutput("Variables:\n");
    writeOutput("  \"search_text\" Text to search for (required)\n");
    writeOutput("  [file/dir]    File or directory to search in\n");
    writeOutput("Options:\n");
    writeOutput("  -q               Quiet mode, no output, only exit code\n");
    writeOutput("  -m {Number}      Maximum number of matches to output\n");
    writeOutput("  -c               Output the count of matches\n");
    writeOutput("  -r               Search recursively in directories\n");
    writeOutput("  -i               Case-insensitive search\n");
    writeOutput("  -h               Show this help message\n");
    writeOutput("  \"search_text\" -  Read input from stdin\n");
}

void setStandardArgs(GrepOptions *options) {
    options->quiet = false;
    options->max_count_set = false;
    options->max_count = 0;
    options->count = false;
    options->recursive = false;
    options->case_insensitive = false;
    options->from_stdin = false;
    options->search_text = NULL;
    options->file_or_dir = NULL;
}

void parse_arguments(int argc, char *argv[], GrepOptions *options) {
    int opt;
    char *endptr;

    setStandardArgs(options);

    while ((opt = getopt(argc, argv, "qm:crih")) != -1) {
        switch (opt) {
            case 'q':
                options->quiet = true;
                break;
            case 'm':
                options->max_count_set = true;
                options->max_count = strtol(optarg, &endptr, 10);

                if (*endptr != '\0') {
                    writeError("Error: Invalid number for -m option.\n");
                    exit(EXIT_FAILURE);
                }

                if (options->max_count < 0) {
                    writeError("Error: Invalid number for -m option.\n");
                    exit(EXIT_FAILURE);
                }
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
            case 'h':
                print_usage();
                exit(EXIT_SUCCESS);
            case '?':
            default:
                print_usage();
                exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        writeError("Error: search_text is required.\n");
        print_usage();
        exit(EXIT_FAILURE);
    }

    options->search_text = argv[optind++];

    if (strcmp(options->search_text, "-") == 0) {
        writeError("Error: - must be put after the search_text to enable stin.\n");
        print_usage();
        exit(EXIT_FAILURE);
    }

    if (optind < argc) {
        options->file_or_dir = argv[optind++];

        if (strcmp(options->file_or_dir, "-") == 0) {
            options->from_stdin = true;
        }
    }

    if (optind < argc) {
        writeError("Error: Too many arguments.\n");
        print_usage();
        exit(EXIT_FAILURE);
    }
}

void validate_arguments(GrepOptions *options) {

    if (options->from_stdin){
       if (options->file_or_dir != NULL && strcmp(options->file_or_dir, "-") != 0) {
           writeError("Error: You must specify a file or directory unless reading from stdin (-).\n");
           exit(EXIT_FAILURE);
       }
         if (options->recursive) {
             writeError("Error: Cannot use -r when reading from stdin.\n");
             print_usage();
             exit(EXIT_FAILURE);
        }
       } else {
           if (options->file_or_dir == NULL) {
               writeError("Error: You must specify a file unless reading from stdin (-).\n");
               exit(EXIT_FAILURE);
           }
    }
}
