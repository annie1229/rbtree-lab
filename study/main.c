#include "binary_tree.h"
#include "stack.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum { DFS, BFS, searchDFS, searchBFS } mode;

void bst_DFS(Node* root, Stack* stack);
void bst_BFS(Node* root, Queue* queue);
Node* bst_searchDFS(Node* root, Stack* stack, int data, size_t count);
Node* bst_searchBFS(Node* root, Queue* queue, int data);

Node* root;     // 이렇게만 선언하면 Node에 대한 포인터의 메모리만 잡히고 동적할당을 해줘야 비로소 구조체를 담는 공간을 가지는 Node애 대한 메모리가 잡힘
Stack* newStack;
Queue* newQueue;

int main() {
    newStack = malloc(sizeof(Stack));   // malloc 동적할당 해줘야하는 이유 >> 메모리를 효율적으로 쓰기 위한것 뿐만 아니라,  동적할당을 안하고 newNode->data에 값을 할당하려 해도 메모리에 잡힌것이 없으므로 에러가 나게 됨
    newStack->top = 0;

    newQueue = malloc(sizeof(Queue));
    newQueue->head = 0;
    newQueue->tail = 0;
    newQueue->size = 0;

    root = bst_insert(root, 5);
    root = bst_insert(root, 9);
    root = bst_insert(root, 3);
    root = bst_insert(root, 1);
    root = bst_insert(root, 7);
    root = bst_insert(root, 4);
    root = bst_insert(root, 11);
    root = bst_insert(root, 17);
    root = bst_insert(root, 6);

    bst_print(root);
    printf("delete 11\n");
    root = bst_delete(root,5);
    bst_print(root);

    mode m = DFS;

    switch (m) {
    case DFS:
        printf("\n------DFS------\n");
        bst_DFS(root, newStack);
        break;
    case BFS:
        printf("\n------BFS------\n");
        bst_BFS(root, newQueue);
        break;
    case searchDFS:
        printf("\n------searchDFS------\n");
        bst_searchDFS(root, newStack, 9 ,1);
        break;
    case searchBFS:
        printf("\n------searchBFS------\n");
        bst_searchBFS(root, newQueue, 9);
        break;
    }

    return 0;
}


void bst_DFS(Node* root, Stack* stack) {
    if (!root->flag) {
        root->flag = true;
        push(stack, root);
    }

    if (root->left && !root->left->flag) {
        bst_DFS(root->left, stack);
    }
    else if (root->right && !root->right->flag) {
        bst_DFS(root->right, stack);
    }
    else {
        pop(stack); 

        if (stack->top == 0) {
            printf("\nfinish DFS!!\n");
        }
        else {
            Node* parentNode = stack->arr[stack->top - 1];
            bst_DFS(parentNode, stack);
        }
    }

}

void bst_BFS(Node* root, Queue* queue) {
    enqueue(queue, root);

    while (queue->size != 0) {
        Node* parentNode = dequeue(queue);

        if (parentNode->left) {
            enqueue(queue, parentNode->left);
        }
        if (parentNode->right) {
            enqueue(queue, parentNode->right);
        }
    }
    printf("\nfinish BFS!!\n");
}

Node* bst_searchDFS(Node* root, Stack* stack, int data, size_t count) {
    if (!root->flag) {
        if (root->data == data) {
            printf("[searchDFS] search %d, count %ld\n", data, count);
            return root;
        }
        root->flag = true;
        push(stack, root);
        count++;
    }

    if (root->left && !root->left->flag) {
        bst_searchDFS(root->left, stack, data, count);
    }
    else if (root->right && !root->right->flag) {
        bst_searchDFS(root->right, stack, data, count);
    }
    else {
        pop(stack);

        if (stack->top == 0) {
            printf("\n[searchDFS] can't search %d\n", data);
        }
        else {
            Node* parentNode = stack->arr[stack->top - 1];
            bst_searchDFS(parentNode, stack, data, count);
        }
    }

}

Node* bst_searchBFS(Node* root, Queue* queue, int data) {
    size_t count = 1;

    if (root->data == data) {
        printf("[searchBFS] search %d, count %ld\n", data, count);
        return root;
    }

    enqueue(queue, root);
    count++;
    
    while (queue->size != 0) {
        Node* parentNode = dequeue(queue);

        if (parentNode->left) {
            if(parentNode->left->data == data) {
                printf("[searchBFS] search %d, count %ld\n", data, count);
                return parentNode->left;
            }

            enqueue(queue, parentNode->left);
            count++;
        }
        if (parentNode->right) {
            if (parentNode->right->data == data) {
                printf("[searchBFS] search %d, count %ld\n", data, count);
                return parentNode->right;
            }

            enqueue(queue, parentNode->right);
            count++;
        }
    }
    printf("\n[searchBFS] can't search %d\n", data);
}