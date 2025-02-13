#include "recursive.h"
#include "output.h"

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

    DIR *dir = opendir(glob);

    if (!dir) {
        writeError("Error opening directory");
        return entryCount;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;  // Skip current and parent directories
        }
        entryCount++;

        char fullpath[PATH_MAX];
        snprintf(fullpath, PATH_MAX, "%s/%s", glob, entry->d_name);
        if (entryCount >= capacity) {
            capacity = 2 * entryCount;
            File* temp = realloc(*fileList, capacity * sizeof(File));
            if (temp == NULL) {
                writeError("Error allocating memory");
                closedir(dir);
                return entryCount;
            }
            *fileList = temp;
        }
        if (entry->d_type == DT_REG) {

            strncpy((*fileList)[entryCount-1].fileName, fullpath, PATH_MAX-1);
            (*fileList)[entryCount-1].fileName[PATH_MAX - 1] = '\0';  // Ensure null-termination
            strcpy((*fileList)[entryCount-1].content, "");  // Empty content for now
        }
        if (entry->d_type == DT_DIR) {
            entryCount = getFilesInDir(fileList, fullpath, entryCount, capacity);
        }
    }
    closedir(dir);
    return entryCount;
}
