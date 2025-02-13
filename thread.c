#include <pthread.h>
#include <string.h>

#include "thread.h"
#include "readFile.h"
#include "search.h"

void *greppyThread(void *arg) {
    ThreadData *data = arg;

    File *file = data->file;

    char *content = readFile(file->fileName, data->case_insensitive);

    if (content == NULL) {
        pthread_exit(NULL);
    }
    strcpy(file->content, content);
    free(content);

    char *searchText = data->searchText;

    search(file->content, searchText, &data->results);

    free(searchText);

    pthread_exit(NULL);
}
