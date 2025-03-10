//
// Created by Adrian Stelter on 11.02.25.
//

#ifndef THREAD_H
#define THREAD_H

#include "linkedList.h"
#include "recursive.h"
#include <stdbool.h>

typedef struct {
    File *file;
    Node *results;
    char *searchText;
    bool case_insensitive;
} ThreadData;

void *greppyThread(void *arg);

#endif //THREAD_H
