#include "linkedList.h"
#include <stddef.h>

int count(Node** head) {
    int counter = 0;

    Node* temp = *head;
    while (temp != NULL) {
        counter++;
        temp = temp->next;
    }

    return counter;
}