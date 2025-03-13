#ifndef RANDOMIZED_QUEUE_H
#define RANDOMIZED_QUEUE_H

#include <stddef.h>
#include <stdbool.h>

typedef void* Item;

typedef struct RandomizedQueue* RandomizedQueuePtr;

RandomizedQueuePtr RandomizedQueueInit();

bool RandomizedQueueEmpty(RandomizedQueuePtr rq);

size_t RandomizedQueueSize(RandomizedQueuePtr rq);

void RandomizedQueueEnqueue(RandomizedQueuePtr rq, Item item);

Item RandomizedQueueDequeue(RandomizedQueuePtr rq);

void RandomizedQueueDestroy(RandomizedQueuePtr rq);

#endif 

