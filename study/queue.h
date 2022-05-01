#ifndef _QUEUE_H_
#define _QUEUE_H_

#define QUEUE_SIZE 10
#include "binary_tree.h"
#include <stdio.h>

typedef struct Queue {
    int arr[QUEUE_SIZE];
    int head;
    int tail;
    size_t size;
} Queue;

void enqueue(Queue* queue, Node* node);
Node* dequeue(Queue* queue);

#endif  // _QUEUE_H_