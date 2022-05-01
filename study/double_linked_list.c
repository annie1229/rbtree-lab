#include "double_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* head;
Node* tail;

int main()
{
    head = malloc(sizeof(Node));
    tail = malloc(sizeof(Node));
    head->next = tail;
    tail->prev = head;

    d_linked_list_add(2);
    d_linked_list_add(3);
    d_linked_list_add(4);
    d_linked_list_insert(1, 0);
    d_linked_list_delete(4);
    d_linked_list_searchFront(3);
    d_linked_list_searchBack(3);
    d_linked_list_add(7);
    d_linked_list_add(9);
    d_linked_list_insert(8, 5);
    d_linked_list_delete(1);
    d_linked_list_delete(5);
    d_linked_list_insert(8, 3);
    d_linked_list_insert(6, 9);
    d_linked_list_searchFront(9);
    d_linked_list_searchBack(1);

    return 0;
}

void d_linked_list_add(int data) {
    if (head->next == tail) {
        Node* newNode = malloc(sizeof(Node));
        newNode->next = tail;
        newNode->prev = head;
        newNode->data = data;
        head->next = newNode;
        tail->prev = newNode;
    }
    else {
        Node* cursorNode = head;

        while (cursorNode->next != tail) {
            cursorNode = cursorNode->next;
        }

        Node* newNode = malloc(sizeof(Node));
        newNode->next = tail;
        newNode->prev = cursorNode;
        newNode->data = data;
        cursorNode->next = newNode;
        tail->prev = newNode;
    }

    printf("[add] add %d \n", data);
    d_linked_list_print();
}

void d_linked_list_insert(int data, int index) {
    Node* cursorNode = head;
    int count = 0;

    while (cursorNode->next != tail) {
        if (count == index) {
            Node* newNode = malloc(sizeof(Node));
            newNode->next = cursorNode->next;
            newNode->prev = cursorNode;
            cursorNode->next = newNode;
            newNode->data = data;

            printf("[insert] insert %d into index %d\n", data, index);
            d_linked_list_print();

            return;
        }
        cursorNode = cursorNode->next;
        count++;
    }

    if (count == index) {
        d_linked_list_add(data);
        return;
    }

    printf("[insert error] error can't insert %d into index %d (length is %d)\n", data, index, count);
    d_linked_list_print();
}

void d_linked_list_delete(int data) {
    Node* cursorNode = head;
    Node* prevNode = head;
    Node* nextNode = head->next;

    while (cursorNode->next != tail) {
        if (cursorNode->data == data) {
            if (cursorNode->next != tail) {
                prevNode->next = cursorNode->next;
                nextNode->prev = prevNode;
            }
            else {
                prevNode->next = tail;
                tail->prev = prevNode;
            }

            printf("[delete] delete %d \n", data);
            d_linked_list_print();
            free(cursorNode);

            return;
        }
        prevNode = cursorNode;
        cursorNode = cursorNode->next;
        nextNode = cursorNode->next;
    }

    printf("[delete error] can't find %d \n", data);
    d_linked_list_print();
    return;
}

int d_linked_list_searchFront(int data) {
    Node* cursorNode = head->next;

    int count = 0;

    while (cursorNode != tail) {
        if (cursorNode->data == data) {
            printf("[searchFront] search %d on index %d from the front.\n", data, count);
            d_linked_list_print();
            return count;
        }
        cursorNode = cursorNode->next;
        count++;
    }

    printf("[search error] can't find %d \n", data);
    d_linked_list_print();
    return -1;
}

int d_linked_list_searchBack(int data) {
    Node* cursorNode = tail->prev;

    int count = 0;

    while (cursorNode != head) {
        if (cursorNode->data == data) {
            printf("[searchBack] search %d on index %d from the back.\n", data, count);
            d_linked_list_print();
            return count;
        }
        cursorNode = cursorNode->prev;
        count++;
    }

    printf("[search error] can't find %d \n", data);
    d_linked_list_print();
    return -1;
}

void d_linked_list_print() {
    Node* cursorNode = head;
    printf("[");

    while (cursorNode->next != tail) {
        cursorNode = cursorNode->next;
        printf("%d, ", cursorNode->data);
    }

    printf("]\n");
}