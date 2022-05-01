#include "binary_tree.h"

#include <stdio.h>
#include <stdlib.h>

Node* bst_insert(Node* cursorNode, int data) {
    if (cursorNode == NULL) {
        cursorNode = malloc(sizeof(Node));
        cursorNode->right = NULL;
        cursorNode->left = NULL;
        cursorNode->data = data;
        cursorNode->flag = false;

        return cursorNode;
    }
    else {
        if (data < cursorNode->data) {
            cursorNode->left = bst_insert(cursorNode->left, data);
        }
        else {
            cursorNode->right = bst_insert(cursorNode->right, data);
        }
    }

    cursorNode->flag = false;
    return cursorNode;
}

Node* bst_delete(Node* root, int data) {
   Node* delNode = NULL;
   Node* parentNode = NULL;
   Node* successor = NULL;
   Node* predecessor = NULL;
   Node* child = NULL;

   delNode = root;
   while(delNode != NULL) {
       if(data == delNode->data) {
           break;
       }
       parentNode = delNode;
       if(data < delNode->data) {
           delNode = delNode->data;
       } else {
           delNode = delNode->right;
       }
   }

   if(delNode == NULL) {
       printf("can't delete node! no data");
       return root;
   }

   if(delNode->left == NULL && delNode->right == NULL) {
       if(parentNode != NULL) {
           if(parentNode->left == delNode) {
               parentNode->left = NULL;
           } else {
               parentNode->right = NULL;
           }
       } else {
           root = successor;
       }
   } else if(delNode->left != NULL && delNode->right != NULL){    // 삭제할 노드의 자식 노드가 2개인 경우 
        predecessor = delNode;
        successor = delNode->left;
        
        while(successor->right != NULL){    // 왼쪽 서브트리에서 가장 큰 값 찾기 
            predecessor = successor;
            successor = successor->right;
        }
        
        predecessor->right = successor->left;    // successor의 자식 노드 위치 변경 
        successor->left = delNode->left;    // successor를 삭제할 노드의 위치로 옮긴 것과 같음 
        successor->right = delNode->right;     
        
        if(parentNode != NULL){    // 삭제할 노드의 부모노드가 있을 때 
            if(parentNode->left == delNode){
                parentNode->left = successor;
            }else{
                parentNode->right = successor;
            }
        }else{
            root = successor;
        }
    } else {
       if(delNode->left != NULL) {
           child = delNode->left;
       } else {
           child = delNode->right;
       }

       if(parentNode != NULL) {
           if(parentNode->left == delNode) {
               parentNode->left = child;
           } else {
               parentNode->right = child;
           }
       } else {
           root = child;
       }
   }
   free(delNode);
   return root;
}

void bst_print(Node* root) {
    if (root == NULL)
    {
        return;
    }

    printf("NODE [%d] > ", root->data);

    if (root->left != NULL)
    {
        printf("LEFT [%d] ", (root->left)->data);
    }
    if (root->right != NULL)
    {
        printf("RIGHT [%d]", (root->right)->data);
    }
    printf("\n");

    if (root->left)
    {
        bst_print(root->left);
    }
    if (root->right)
    {
        bst_print(root->right);
    }
}