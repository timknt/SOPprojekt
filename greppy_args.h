#ifndef GREPPY_ARGS_H
#define GREPPY_ARGS_H

#include <stdbool.h>

typedef struct {
    bool quiet;
    bool max_count_set;
    int max_count;
    bool count;
    bool recursive;
    bool case_insensitive;
    bool from_stdin;
    const char *search_text;
    const char *file_or_dir;
} GrepOptions;

void print_usage(const char *prog_name);
void parse_arguments(int argc, char *argv[], GrepOptions *options);
void validate_arguments(GrepOptions *options);

#endif // GREPPY_ARGS_H
