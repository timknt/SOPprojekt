#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>


void search(const char *filename, const char *search_text, int max_count){
    struct stat path_stat;
    if (stat(filename, &path_stat) != 0) {
        return;  // Error (e.g., file does not exist)
    }
    if (S_ISDIR(path_stat.st_mode)){
        search_in_directory(filename, search_text, max_count);
    }else{
        search_in_file(filename, search_text, max_count);
    }
}

void search_in_file(const char *filename, const char *search_text, int max_count) {
    char *content = readFile((char *)filename);
    if (!content) {
        fprintf(stderr, "Error reading file: %s\n", filename);
        return;
    }

    int count = 0;
    char *line = strtok(content, "\n");
    while (line && (max_count == -1 || count < max_count)) {
        if (strstr(line, search_text)) {
            printf("%s: %s\n", filename, line);
            count++;
        }
        line = strtok(NULL, "\n");
    }

    free(content);
}

void search_in_directory(const char *dir_name, const char *search_text, int max_count) {
    DIR *dir = opendir(dir_name);
    if (!dir) {
        fprintf(stderr, "Error opening directory: %s\n", dir_name);
        return;
    }

    struct dirent *entry;
    struct stat path_stat;

    while ((entry = readdir(dir)) != NULL) {
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);

        stat(path, &path_stat);
        if (S_ISDIR(path_stat.st_mode) && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            search_in_directory(path, search_text, max_count);
        } else if (S_ISREG(path_stat.st_mode)) {
            search_in_file(path, search_text, max_count);
        }
    }
    closedir(dir);
}