#include "stack.h"

void push(Stack* stack, Node* node) {
    if (stack->top < STACK_SIZE) {
        stack->arr[stack->top++] = node;
        printf("<< push %d\n", node->data);
    }
    else {
        printf("[error] stack overflow! size is %d\n", STACK_SIZE);
    }
};

Node* pop(Stack* stack) {
    if (stack->top > 0) {
        Node* popNode = stack->arr[--stack->top];
        stack->arr[stack->top] = NULL;
        printf(" >> pop %d\n", popNode->data);
        return popNode;
    }
    else {
        printf("'[error] stack is empty!\n");
        return NULL;
    }
};
