#ifndef GREPPY_ARGS_H
#define GREPPY_ARGS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "output.h"

typedef struct {
    bool quiet;
    bool max_count_set;
    int max_count;
    bool count;
    bool recursive;
    bool case_insensitive;
    bool from_stdin;
    char *search_text;
    char *file_or_dir;
} GrepOptions;

void print_usage();
void parse_arguments(int argc, char *argv[], GrepOptions *options);
void validate_arguments(GrepOptions *options);

#endif // GREPPY_ARGS_H
