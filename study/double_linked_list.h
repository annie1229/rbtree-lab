#ifndef _DOUBLE_LINKEDLIST_H_
#define _DOUBLE_LINKEDLIST_H_

typedef struct Node {
    struct Node* next;
    struct Node* prev;
    int data;
} Node;

void d_linked_list_add(int data);
void d_linked_list_insert(int data, int index);
void d_linked_list_delete(int data);
int d_linked_list_searchFront(int data);
int d_linked_list_searchBack(int data);
void d_linked_list_print();

#endif  // _DOUBLE_LINKEDLIST_H_