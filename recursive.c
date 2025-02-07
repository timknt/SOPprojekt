//
// Created by Adrian Stelter on 03.02.25.
//
#include "recursive.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_MAX 4096


int filter(const struct dirent *name)
{
    return 1;
}

int getFilesInDir(File **fileList, char *glob, int position, int capacity) {
    struct dirent *entry;
    int entryCount = position;
    printf("Searching Path: %s\n", glob);

    DIR *dir = opendir(glob);

    if (!dir) {
        perror("Error opening directory");
        return entryCount;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;  // Skip current and parent directories
        }
        entryCount++;

        char fullpath[PATH_MAX];
        snprintf(fullpath, 256, "%s/%s", glob, entry->d_name);
        printf("Found: %s \n", fullpath);
        if (entryCount > capacity) {
            capacity = 2 * entryCount;
            File* temp = realloc(*fileList, capacity * sizeof(File));
            *fileList = temp;
        }
        if (entry->d_type == DT_REG) {

            strncpy((*fileList)[entryCount-1].fileName, fullpath, PATH_MAX);
            (*fileList)[entryCount-1].fileName[PATH_MAX - 1] = '\0';  // Ensure null-termination
            strcpy((*fileList)[entryCount-1].content, "");  // Empty content for now
        }
        if (entry->d_type == DT_DIR) {
            entryCount += getFilesInDir(fileList, fullpath, entryCount-1, capacity);
        }
    }
    closedir(dir);
    return entryCount - position -1;
}
