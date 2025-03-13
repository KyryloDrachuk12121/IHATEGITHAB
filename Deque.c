#include "Deque.h"
#include <stdlib.h>
#include <assert.h>

typedef struct Node {
    Item item;
    struct Node* next;
    struct Node* prev;
} Node;

struct Deque {
    Node* head;
    Node* tail;
    size_t size;
};

DequePtr DequeInit() {
    DequePtr deque = (DequePtr)malloc(sizeof(struct Deque));
    if (deque == NULL) {
        return NULL;
    }
    deque->head = NULL;
    deque->tail = NULL;
    deque->size = 0;
    return deque;
}

int DequeEmpty(DequePtr deque) {
    assert(deque != NULL);
    return deque->size == 0;
}

size_t DequeSize(DequePtr deque) {
    assert(deque != NULL);
    return deque->size;
}

void DequeAddFirst(DequePtr deque, Item item) {
    assert(deque != NULL);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return;
    }
    newNode->item = item;
    newNode->prev = NULL;
    newNode->next = deque->head;
    if (deque->head != NULL)
        deque->head->prev = newNode;
    deque->head = newNode;
    if (deque->tail == NULL)
        deque->tail = newNode;
    deque->size++;
}

void DequeAddLast(DequePtr deque, Item item) {
    assert(deque != NULL);
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return;
    }
    newNode->item = item;
    newNode->next = NULL;
    newNode->prev = deque->tail;
    if (deque->tail != NULL)
        deque->tail->next = newNode;
    deque->tail = newNode;
    if (deque->head == NULL)
        deque->head = newNode;
    deque->size++;
}

Item DequeRemoveFirst(DequePtr deque) {
    assert(deque != NULL);
    if (DequeEmpty(deque)) {
        return NULL;
    }
    Node* temp = deque->head;
    Item item = temp->item;
    deque->head = temp->next;
    if (deque->head != NULL)
        deque->head->prev = NULL;
    else
        deque->tail = NULL;
    free(temp);
    deque->size--;
    return item;
}

Item DequeRemoveLast(DequePtr deque) {
    assert(deque != NULL);
    if (DequeEmpty(deque)) {
        return NULL;
    }
    Node* temp = deque->tail;
    Item item = temp->item;
    deque->tail = temp->prev;
    if (deque->tail != NULL)
        deque->tail->next = NULL;
    else
        deque->head = NULL;
    free(temp);
    deque->size--;
    return item;
}

void DequeDestroy(DequePtr deque) {
    if (deque == NULL)
        return;
    Node* current = deque->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(deque);
}

#ifdef BUILD_MAIN
#include <stdio.h>
int main(void) {
    DequePtr dq = DequeInit();
    if (!dq) {
        printf("Error creating deque\n");
        return 1;
    }
    printf("Deque created successfully\n");

    int a = 10, b = 20;
    DequeAddFirst(dq, &a);
    DequeAddLast(dq, &b);
    printf("Deque size after additions: %zu\n", DequeSize(dq));

    int* removed = (int*)DequeRemoveFirst(dq);
    printf("Removed element: %d\n", *removed);
    printf("Deque size after removal: %zu\n", DequeSize(dq));

    DequeDestroy(dq);
    return 0;
}
#endif


