#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack* StackInit() {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    if (s == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    s->top = NULL;
    return s;
}

int StackEmpty(Stack* s) {
    return (s->top == NULL);
}

void push(Stack* s, Item item) {
    StackNode* node = (StackNode*)malloc(sizeof(StackNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->item = item;
    node->next = s->top;
    s->top = node;
}

Item pop(Stack* s) {
    if (StackEmpty(s)) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    StackNode* temp = s->top;
    Item item = temp->item;
    s->top = temp->next;
    free(temp);
    return item;
}

void StackDestroy(Stack* s) {
    while (!StackEmpty(s)) {
        pop(s);
    }
    free(s);
}
