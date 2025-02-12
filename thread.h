//
// Created by Adrian Stelter on 11.02.25.
//

#ifndef THREAD_H
#define THREAD_H

#include "linkedList.h"
#include "recursive.h"

typedef struct {
    File *file;
    Node *results;
    char *searchText;
} ThreadData;

void *greppyThread(void *arg);

#endif //THREAD_H
