#ifndef _BST_H_
#define _BST_H_

#include <stdbool.h>

typedef struct Node {    // 구조체 이름
    struct Node* left;  // 여기서는 아직 struct를 붙여줘야함,
    struct Node* right; // typedef를 사용했지만 아직 정의가 끝나지 않은 상태에서 자기 참조를 하므로 별칭 사용 불가능
    int data;
    bool flag;
} Node;                 // 별칭

Node* bst_insert(Node* cursorNode, int data);
Node* bst_delete(Node* root, int data);
void bst_print(Node* root);

#endif  // _BST_H_