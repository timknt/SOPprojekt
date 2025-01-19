#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Data {
    char text[256];
    int line;
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

void concatenateLists(Node** head1, Node* head2);

#endif
