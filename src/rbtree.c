#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

rbtree *new_rbtree(void) { // 새로운 rbtree 만드는 함수
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree)); // rbtree 구조체 크기만큼 동적할당
  // TODO: initialize struct if needed
  node_t *nil = (node_t *)calloc(1, sizeof(node_t)); // node_t 구조체 크기만큼 동적할당
  nil->color = RBTREE_BLACK; // nil노드는 black
  p->root = p->nil = nil; // 처음에는 트리가 빈 상태(root == nil)
  return p; // rbtree에 대한 포인터변수 반환
}

void delete_node(rbtree *t, node_t *node) { // 후위순회 방식(post-order)으로 돌면서 노드 메모리 해제
     if(node->left != t->nil) { // 왼쪽 자식 남아있으면 왼쪽 끝까지 내려가기
         delete_node(t, node->left);
     }
     if(node->right != t->nil) { // 오른쪽 자식 남아있으면 오른쪽 끝까지 내려가기
         delete_node(t, node->right);
     }
     free(node); // 자식들 다 지웠으면 서브트리의 루트노드 메모리 해제
     node = NULL; // 메모리 해제 되어도 포인터에 들어있는 값이 지워지는건 아니므로 NULL로 바꿔준다.
}

void delete_rbtree(rbtree *t) { // rbtree 메모리 해제하는 함수
  // TODO: reclaim the tree nodes's memory
  if(t->root != t->nil) { // 트리안에 노드들이 있으면
      delete_node(t, t->root); // 노드들 돌면서 메모리 해제
  }
  free(t->nil); // nil노드 메모리 해제
  free(t); // rbtree 구조체 담았던 메모리 해제
}

void left_rotation(rbtree *t, node_t *x) { // x 기준으로 왼쪽 회전
    node_t *y = x->right; // x의 오른쪽 자식 y에 담기
    x->right = y->left; // y의 왼쪽 자식을 x의 오른쪽 자식으로 변경
    if(y->left != t->nil) { // y의 왼쪽 자식이 nil노드가 아니었으면
        y->left->parent = x; // y의 왼쪽 자식 노드의 parent가 x가 되도록 변경
    }
    y->parent = x->parent; // x의 부모가 y의 부모가 되도록
    if(x->parent == t->nil) { // 만약 x가 루트노드였다면
        t->root = y; // 루트노드를 y로 변경
    } else if(x == x->parent->left) { // x가 왼쪽 자식이었다면
        x->parent->left = y; // 왼쪽 자식 자리에 y넣기
    } else { // x가 오른쪽 자식이었다면
        x->parent->right = y; // 오른쪽 자식 자리에 y넣기
    }
    y->left = x; // y의 왼쪽 자식은 x으로 변경
    x->parent = y; // x의 부모는 y로 변경
}

void right_rotation(rbtree *t, node_t *y) { // y 기준으로 오른쪽 회전
    node_t *x = y->left; // y의 왼쪽 자식 x에 담기
    y->left = x->right; // x의 오른쪽 자식을 y의 왼쪽 자식으로 변경
    if(x->right != t->nil) { // x의 오른쪽 자식이 nil노드가 아니었으면
        x->right->parent = y; // x의 오른쪽 자식의 부모를 y로 변경
    }
    x->parent = y->parent; // y의 부모가 x의 부모가 되도록
    if(y->parent == t->nil) { // y가 루트노드였으면
        t->root = x; // 루트노드를 x로 변경
    } else if(y == y->parent->right) { // y가 오른쪽 자식이었다면
        y->parent->right = x; // 오른쪽 자식 자리에 x넣기
    } else { // y가 왼쪽 자식이었다면
        y->parent->left = x; // 왼쪽 자식 자리에 x넣기
    }
    x->right = y; // x의 오른쪽 자식은 y
    y->parent = x; // y의 부모는 x로 변경
}

node_t *rbtree_insert(rbtree *t, const key_t key) { // key값 받아서 새로운 노드 삽입하는 함수
  // TODO: implement insert
    node_t *parent = t->nil; // 삽입할 위치의 부모노드 담을 변수
    node_t *next = t->root;
    node_t *uncle; // 삼촌노드(부모의 형제노드)
    node_t *newNode = (node_t *)calloc(1, sizeof(node_t)); // 새로운 노드 메모리 할당
    newNode->key = key; // 입력받은 key값 넣어주기
    while(next != t->nil) { // 리프노드에 도달할 때까지 반복
        parent = next; // 부모노드 갱산
        if(key < next->key) { // 입력받은 key값이 현재 노드의 key값보다 작으면
            next = next->left; // 왼쪽 자식 탐색
        } else { // 입력받은 key값이 현재 노드의 key값보다 크면
            next = next->right; // 오른쪽 자식 탐색
        }
    }
    newNode->parent = parent; // 현재 parent노드를 새로만든 노드의 parent에 담기
    if(parent == t->nil) { // 만약 현재 노드가 루트노드면
        t->root = newNode; // 루트노드에 새로만든 노드 담기
    } else if(key < parent->key) { // 새로만든 노드의 key값이 부모의 key값보다 작으면
        parent->left = newNode; // parent의 왼쪽 자식에 새로만든 노드 담기
    } else { // 새로만든 노드의 key값이 부모의 key값보다 크면
        parent->right = newNode; // parent의 오른쪽 자식에 새로만든 노드 담기
    }
    newNode->left = newNode->right = t->nil; 
    newNode->color = RBTREE_RED; // 새로만든 노드는 빨간색으로

    while(newNode->parent->color == RBTREE_RED) { // 새로 만든 노드의 부모도 빨간색이면
        if(newNode->parent == newNode->parent->parent->left) { // 부모노드가 조부모노드의 왼쪽 자식이면
            uncle = newNode->parent->parent->right; // 삼촌노드(부모의 형제노드) 담기
            if(uncle->color == RBTREE_RED) { // Case1: 삼촌노드도 빨간색이면
                newNode->parent->color = RBTREE_BLACK; // 부모
                uncle->color = RBTREE_BLACK;
                newNode->parent->parent->color = RBTREE_RED;
                newNode = newNode->parent->parent;
            } else {
                if(newNode == newNode->parent->right) {
                    newNode = newNode->parent;
                    left_rotation(t, newNode);
                }
                newNode->parent->color = RBTREE_BLACK;
                newNode->parent->parent->color = RBTREE_RED;
                right_rotation(t, newNode->parent->parent);
            }
        } else { // 부모노드가 조부모노드의 오른쪽 자식이면
            uncle = newNode->parent->parent->left;
            if(uncle->color == RBTREE_RED) {
                newNode->parent->color = RBTREE_BLACK;
                uncle->color = RBTREE_BLACK;
                newNode->parent->parent->color = RBTREE_RED;
                newNode = newNode->parent->parent;
            } else {
                if(newNode == newNode->parent->left) {
                    newNode = newNode->parent;
                    right_rotation(t, newNode);
                }
                newNode->parent->color = RBTREE_BLACK;
                newNode->parent->parent->color = RBTREE_RED;
                left_rotation(t, newNode->parent->parent);
            }
        }
    }
    t->root->color = RBTREE_BLACK;
    return newNode;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *cur = t->root;
  if (cur == t->nil) {
      return NULL;
  }
//   printf("---find start %d---\n", cur->key);
  while(cur != t->nil && cur->key != key) {
      if(cur->key > key) {
            // printf("%d find small >> %d\n", key, cur->key);    
          cur = cur->left;
      } else {
            // printf("%d find big >> %d\n", key, cur->key); 
          cur = cur->right;
      }
  }
  if(cur->key != key) {
      return NULL;
  }
//   printf("%d find node >> %d\n", key, cur->key);
  return cur;
}

node_t *tree_min(node_t *nil, node_t *p) {
    node_t *cur = p;
    while(cur->left != nil) {
        cur = cur->left;
    }
    return cur;
}

node_t *tree_max(node_t *nil, node_t *p) {
    node_t *cur = p;
    while(cur->right != nil) {
      cur = cur->right;
    }
    return cur;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *cur = t->root;
  cur = tree_min(t->nil, cur);
  return cur;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *cur = t->root;
  cur = tree_max(t->nil, cur);
  return cur;
}

node_t *tree_predecessor(rbtree *t, node_t *x) {
    node_t *prev = x;
    node_t *cur = x->left;
    while(cur != t->nil) {
        prev = cur;
        cur = cur->right;
    }
    return prev;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
    // printf("--%d erase start--\n", p->key);
    node_t *x, *y, *w;

    // 자식노드가 0개인 경우
    if(p->left == t->nil || p->right == t->nil) { 
        y = p;
    } else {
        y = tree_predecessor(t, p);
    }

    if(y->left != t->nil) {
        x = y->left;
    } else {
        x = y->right;
    }

    x->parent = y->parent;

    if(y->parent == t->nil) {
        t->root = x;
    } else if(y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }

    if(y != p) {
        p->key = y->key;
    }

    if(y->color == RBTREE_BLACK) {
        while(x != t->root && x->color == RBTREE_BLACK) {
            if(x == x->parent->left) {
                w = x->parent->right;
                if(w->color == RBTREE_RED) {
                    w->color = RBTREE_BLACK;
                    x->parent->color = RBTREE_RED;
                    left_rotation(t, x->parent);
                    w = x->parent->right;
                }
                if(w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
                    w->color = RBTREE_RED;
                    x = x->parent;
                } else {
                    if(w->right->color == RBTREE_BLACK) {
                        w->left->color = RBTREE_BLACK;
                        w->color = RBTREE_RED;
                        right_rotation(t, w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = RBTREE_BLACK;
                    w->right->color = RBTREE_BLACK;
                    left_rotation(t, x->parent);
                    x = t->root;
                }
            } else {
                w = x->parent->left;
                if(w->color == RBTREE_RED) {
                    w->color = RBTREE_BLACK;
                    x->parent->color = RBTREE_RED;
                    right_rotation(t, x->parent);
                    w = x->parent->left;
                }
                if(w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
                    w->color = RBTREE_RED;
                    x = x->parent;
                } else {
                    if(w->left->color == RBTREE_BLACK) {
                        w->right->color = RBTREE_BLACK;
                        w->color = RBTREE_RED;
                        left_rotation(t, w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = RBTREE_BLACK;
                    w->left->color = RBTREE_BLACK;
                    right_rotation(t, x->parent);
                    x = t->root; // 실제로 트리의 루트가 바뀌는거 아님.. 그냥 while문 탈출하려고
                }
            }
        }
        x->color = RBTREE_BLACK;
  }
//   printf("%d erase %d 현재 루트 %d\n", p->key, y->key, t->root->key);
  free(y);
  return 0;
}

void inorder_rbtree(const rbtree *t, node_t *cur, key_t *arr, size_t n, size_t *cnt) {
    if(cur == t->nil) {
        return;
    }
    inorder_rbtree(t, cur->left, arr, n, cnt);
    if(*cnt < n) {
        arr[(*cnt)++] = cur->key;
    } else {
        return;
    }
    inorder_rbtree(t, cur->right, arr, n, cnt);
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
    node_t *cur = t->root;
    if(cur == t-> nil) {
        return 0;
    }
    
    size_t cnt = 0;
    inorder_rbtree(t, t->root, arr, n, &cnt);
    return 0;
}