#ifndef READFILE_H
#define READFILE_H

#include <stdio.h>
#include <stdbool.h>

long readFileSize(FILE *file);

// if called, free returned char array
char *readFile(char *filename, bool case_insensitive);

int testReadFile();

#endif