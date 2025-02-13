//
// Created by Adrian Stelter on 03.02.25.
//

#ifndef RECURSIVE_H
#define RECURSIVE_H

#define PATH_MAX 4096

typedef struct {
    char fileName[PATH_MAX];
    char content[16384];  // Adjust size if needed
} File;

int getFilesInDir(File **fileList, char *glob, int position, int capacity);

#endif //RECURSIVE_H
