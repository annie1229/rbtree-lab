#ifndef _STACK_H_
#define _STACK_H_

#define STACK_SIZE 10

#include "binary_tree.h"
#include <stdio.h>

typedef struct Stack {
    int arr[STACK_SIZE];
    int top;
} Stack;

void push(Stack* stack, Node* node);
Node* pop(Stack* stack);

#endif  // _STACK_H_