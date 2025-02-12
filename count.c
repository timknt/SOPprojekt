//
// Created by Adrian Stelter on 31.01.25.
//

#include <stddef.h>

#include "linkedList.h"

int count(Node** head, const int max) {
    int counter = 0;

    Node* temp = *head;
    while (temp != NULL) {
        counter++;
        if (max > 0 && counter == max) {
            return counter;
        }
        temp = temp->next;
    }

    return counter;
}

int countNoLimit(Node** head) {
    return count(head, -1);
}