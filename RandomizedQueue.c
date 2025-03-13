#include "RandomizedQueue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#define INITIAL_CAPACITY 4

struct RandomizedQueue {
    Item* data; 
    size_t size;      
    size_t capacity;   
};

RandomizedQueuePtr RandomizedQueueInit() {
    RandomizedQueuePtr rq = (RandomizedQueuePtr)malloc(sizeof(struct RandomizedQueue));
    if (rq == NULL) {
        return NULL;
    }
    rq->size = 0;
    rq->capacity = INITIAL_CAPACITY;
    rq->data = (Item*)malloc(rq->capacity * sizeof(Item));
    if (rq->data == NULL) {
        free(rq);
        return NULL;
    }
    return rq;
}

bool RandomizedQueueEmpty(RandomizedQueuePtr rq) {
    assert(rq != NULL);
    return rq->size == 0;
}

size_t RandomizedQueueSize(RandomizedQueuePtr rq) {
    assert(rq != NULL);
    return rq->size;
}

void RandomizedQueueEnqueue(RandomizedQueuePtr rq, Item item) {
    assert(rq != NULL);
    if (rq->size == rq->capacity) {
        size_t newCapacity = rq->capacity * 2;
        Item* newData = (Item*)realloc(rq->data, newCapacity * sizeof(Item));
        if (newData == NULL) {
            return; 
        }
        rq->data = newData;
        rq->capacity = newCapacity;
    }
    rq->data[rq->size++] = item;
}

Item RandomizedQueueDequeue(RandomizedQueuePtr rq) {
    assert(rq != NULL);
    if (rq->size == 0) {
        return NULL; // Порожня черга
    }
    int randIndex = rand() % rq->size;
    Item item = rq->data[randIndex];
    rq->data[randIndex] = rq->data[rq->size - 1];
    rq->size--;
    if (rq->size > 0 && rq->size <= rq->capacity / 4) {
        size_t newCapacity = rq->capacity / 2;
        if (newCapacity < INITIAL_CAPACITY)
            newCapacity = INITIAL_CAPACITY;
        Item* newData = (Item*)realloc(rq->data, newCapacity * sizeof(Item));
        if (newData != NULL) {
            rq->data = newData;
            rq->capacity = newCapacity;
        }
    }
    return item;
}

void RandomizedQueueDestroy(RandomizedQueuePtr rq) {
    if (rq == NULL)
        return;
    free(rq->data);
    free(rq);
}




