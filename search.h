#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#include "readFile.h"

void search(const char *filename, const char *search_text, int max_count);
void search_in_file(const char *filename, const char *search_text, int max_count);
void search_in_directory(const char *dir_name, const char *search_text, int max_count);