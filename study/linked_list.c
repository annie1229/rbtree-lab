#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* head;

int main()
{
    head = malloc(sizeof(Node));
    head->next = NULL;
           
    linked_list_add(5);
    linked_list_add(4);
    linked_list_add(3);
    linked_list_insert(9, 0);
    linked_list_delete(4);
    linked_list_search(3);
    linked_list_add(1);
    linked_list_add(2);
    linked_list_delete(1);
    linked_list_delete(5);
    linked_list_insert(7, 3);
    linked_list_insert(6, 9);
    linked_list_search(9);
    linked_list_search(1);
    linked_list_delete(8);

    return 0;
}

void linked_list_add(int data) {
    if (head->next == NULL) {
        Node* newNode = malloc(sizeof(Node));
        newNode->next = NULL;
        newNode->data = data;
        head->next = newNode;
    }
    else {
        Node* cursorNode = head;

        while (cursorNode->next != NULL) {
            cursorNode = cursorNode->next;
        }

        Node* newNode = malloc(sizeof(Node));
        newNode->next = cursorNode->next;
        newNode->data = data;
        cursorNode->next = newNode;
    }

    printf("[add] add %d \n", data);
    linked_list_print();
}

void linked_list_insert(int data, int index) {
    Node* cursorNode = head;
    int count = 0;

    while (cursorNode->next != NULL) {
        if(count == index) {
            Node* newNode = malloc(sizeof(Node));
            newNode->next = cursorNode->next;
            cursorNode->next = newNode;
            newNode->data = data;

            printf("[insert] insert %d into index %d\n", data, index);
            linked_list_print();

            return;
        }
        cursorNode = cursorNode->next;
        count++;
    }

    if(count == index) {
        linked_list_add(data);
        return;
    }

    printf("[insert error] error can't insert %d into index %d (length is %d)\n", data, index, count);
    linked_list_print();
}

void linked_list_delete(int data) {
    Node* cursorNode = head;
    Node* prevNode = head;

    while (cursorNode->next != NULL) {
        if(cursorNode->data == data) {
            if(cursorNode->next != NULL) {
                prevNode->next = cursorNode->next;
            } else {
                prevNode->next = NULL;
            }

            printf("[delete] delete %d \n", data);
            linked_list_print();
            free(cursorNode);

            return;
        }
        prevNode = cursorNode;
        cursorNode = cursorNode->next;
    }

    printf("[delete error] can't find %d \n", data);
    linked_list_print();
}

int linked_list_search(int data) {
    Node* cursorNode = head->next;

    int count = 0;

    while (cursorNode != NULL) {
        if (cursorNode->data == data) {
            printf("[search] search %d on index %d\n", data, count);
            linked_list_print();
            return count;
        }
        cursorNode = cursorNode->next;
        count++;
    }

    printf("[search error] can't find %d \n", data);
    linked_list_print();
    return -1;
}

void linked_list_print() {
    Node* cursorNode = head;
    printf("[");

    while (cursorNode->next != NULL) {
        cursorNode = cursorNode->next;
        printf("%d, ", cursorNode->data);
    }

    printf("]\n");
}