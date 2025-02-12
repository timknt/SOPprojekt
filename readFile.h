#ifndef READFILE_H
#define READFILE_H

#include <stdio.h>
#include <stdlib.h>

long readFileSize(FILE *file);

// if called, free returned char array
char *readFile(char *filename, bool case_insensitive);

int testReadFile();

#endif