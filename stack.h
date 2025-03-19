#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef void* Item;

typedef struct StackNode {
    Item item;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
} Stack;

Stack* StackInit();
int StackEmpty(Stack* s);
void push(Stack* s, Item item);
Item pop(Stack* s);
void StackDestroy(Stack* s);

#endif