#include "queue.h"

void enqueue(Queue* queue, Node* node) {
    if (queue->size < QUEUE_SIZE) {
        queue->arr[queue->tail % QUEUE_SIZE] = node;
        queue->tail++;
        queue->size++;
        printf("<< enqueue %d\n", node->data);
    }
    else {
        printf("[error] queue is full!\n");
    }
};

Node* dequeue(Queue* queue) {
    if (queue->size > 0) {
        Node* dqNode = queue->arr[queue->head % QUEUE_SIZE];
        queue->head++;
        queue->size--;

        printf("dequeue %d <<\n", dqNode->data);
        return dqNode;
    }
    else {
        printf("'[error] queue is empty!\n");
        return NULL;
    }
};