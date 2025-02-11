#include "linkedList.h"

Node* createNode(Data data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Speicher konnte nicht reserviert werden.\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtTail(Node** head, Data data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void deleteTail(Node** head) {
    if (*head == NULL) {
        printf("Die Liste ist leer.\n");
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    Node* temp = *head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
}

void printList(Node* head) {
    if (head == NULL) {
        printf("Die Liste ist leer.\n");
        return;
    }

    Node* temp = head;
    while (temp != NULL) {
        printf("Text: %s, Line: %d\n", temp->data.text, temp->data.line);
        temp = temp->next;
    }
}

int getLength(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void freeList(Node** head) {
    while (*head != NULL) {
       Node* temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *head = NULL;
}

void concatenateLists(Node** head1, Node** head2) {
    if (*head1 == NULL) {
        *head1 = *head2;
    } else {
        Node* temp = *head1;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = *head2;
    }
    *head2 = NULL;
}

int testLinkedList() {
    Node* head = NULL;

    Data d1 = {"Erster Eintrag", 1};
    Data d2 = {"Zweiter Eintrag", 2};
    Data d3 = {"Dritter Eintrag", 3};

    insertAtTail(&head, d1);
    insertAtTail(&head, d2);
    insertAtTail(&head, d3);

    printf("Liste nach dem Einfügen:\n");
    printList(head);

    deleteTail(&head);
    printf("\nListe nach dem Löschen des letzten Elements:\n");
    printList(head);

    freeList(&head);
    printf("\nListe nach dem Freigeben des Speichers:\n");
    printList(head);

        Node* list1 = NULL;
        Node* list2 = NULL;

        Data d4 = {"List1 - Eintrag 1", 1};
        Data d5 = {"List1 - Eintrag 2", 2};
        Data d6 = {"List2 - Eintrag 1", 3};
        Data d7 = {"List2 - Eintrag 2", 4};

        insertAtTail(&list1, d4);
        insertAtTail(&list1, d5);

        insertAtTail(&list2, d6);
        insertAtTail(&list2, d7);

        printf("Liste 1:\n");
        printList(list1);

        printf("\nListe 2:\n");
        printList(list2);

        concatenateLists(&list1, &list2);

        printf("\nListe 1 nach dem Verbinden:\n");
        printList(list1);

        freeList(&list1);
    return 0;
}


