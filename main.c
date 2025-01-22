#include <stdio.h>
#include "greppy_args.h"

int main(int argc, char *argv[]) {
    GrepOptions options = {0};

    parse_arguments(argc, argv, &options);

    printf("Options:\n");
    printf("  Quiet: %d\n", options.quiet);
    printf("  Max Count Set: %d\n", options.max_count_set);
    printf("  Max Count: %d\n", options.max_count);
    printf("  Count: %d\n", options.count);
    printf("  Recursive: %d\n", options.recursive);
    printf("  Case Insensitive: %d\n", options.case_insensitive);
    printf("  From Stdin: %d\n", options.from_stdin);
    printf("  Search Text: %s\n", options.search_text);
    printf("  File/Dir: %s\n", options.file_or_dir ? options.file_or_dir : "(none)");

    //logic

    return 0;
}