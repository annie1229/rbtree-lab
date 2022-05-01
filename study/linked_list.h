#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

typedef struct Node {
    struct Node* next;
    int data;
} Node;

void linked_list_add(int data);
void linked_list_insert(int data, int index);
void linked_list_delete(int data);
int linked_list_search(int data);
void linked_list_print();

#endif  // _LINKEDLIST_H_