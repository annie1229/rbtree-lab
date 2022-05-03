#include "rbtree.h"
#include <stdio.h>
#include <stdlib.h>

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *nil = (node_t *)calloc(1, sizeof(node_t));
  nil->parent = nil->left = nil->right = NULL;
  nil->color = RBTREE_BLACK;
  p->root = p->nil = nil;
  return p;
}

void delete_node(rbtree *t, node_t *node) {
     if(node->left != t->nil) {
         delete_node(t, node->left);
     }
     if(node->right != t->nil) {
         delete_node(t, node->right);
     }
     free(node);
     node = NULL;
}

void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  if(t->root != t->nil) {
      delete_node(t, t->root);
  }
  free(t->nil);
  free(t);
}

void left_rotation(rbtree *t, node_t *x) {
    node_t *y = x->right;
    x->right = y->left;
    if(y->left != t->nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == t->nil) {
        t->root = y;
    } else if(x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotation(rbtree *t, node_t *y) {
    node_t *x = y->left;
    y->left = x->right;
    if(x->right != t->nil) {
        x->right->parent = y;
    }
    x->parent = y->parent;
    if(y->parent == t->nil) {
        t->root = x;
    } else if(y == y->parent->right) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert
    node_t *parent = t->nil;
    node_t *next = t->root;
    node_t *uncle;
    node_t *newNode = (node_t *)calloc(1, sizeof(node_t));
    newNode->key = key;
    while(next != t->nil) {
        parent = next;
        if(key < next->key) {
            next = next->left;
        } else {
            next = next->right;
        }
    }
    newNode->parent = parent;
    if(parent == t->nil) {
        t->root = newNode;
    } else if(key < parent->key) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    newNode->left = t->nil;
    newNode->right = t->nil;
    newNode->color = RBTREE_RED;

    while(newNode->parent->color == RBTREE_RED) {
        if(newNode->parent == newNode->parent->parent->left) {
            uncle = newNode->parent->parent->right;
            if(uncle->color == RBTREE_RED) {
                newNode->parent->color = RBTREE_BLACK;
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
        } else {
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
//   printf("---find start %d---\n", cur->key);
  while(cur != t->nil && cur->key != key) {
      if(cur->key >= key) {
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

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}