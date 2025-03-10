#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Data {
    char *text;
    int line;
    int startPosition;
    char *fileName;
} Data;

typedef struct Node {
    Data data;
    struct Node* next;
} Node;

Node* createNode(Data data);

void insertAtTail(Node** head, Data data);

void deleteTail(Node** head);

void printList(Node* head);

void freeList(Node** head);

void concatenateLists(Node** head1, Node** head2);

int testLinkedList();

#endif
