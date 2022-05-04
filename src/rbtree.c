#include "rbtree.h"
#include <stdlib.h>

rbtree *new_rbtree(void) {
    rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
    node_t *nil = (node_t *)calloc(1, sizeof(node_t));

    nil->color = RBTREE_BLACK;
    p->root = p->nil = nil;

    return p;
}

void delete_node(rbtree *t, node_t *node) {
    if(node != t->nil) {
        delete_node(t, node->left);
        delete_node(t, node->right);
        free(node);
    }
}

void delete_rbtree(rbtree *t) {
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

void rbtree_insert_fixup(rbtree *t, node_t *new_node) {
    node_t *uncle_node;
    
    while(new_node->parent->color == RBTREE_RED) {
        if(new_node->parent == new_node->parent->parent->left) {
            uncle_node = new_node->parent->parent->right;

            if(uncle_node->color == RBTREE_RED) {
                new_node->parent->color = RBTREE_BLACK;
                uncle_node->color = RBTREE_BLACK;
                new_node->parent->parent->color = RBTREE_RED;
                new_node = new_node->parent->parent;
            } else {
                if(new_node == new_node->parent->right) {
                    new_node = new_node->parent;
                    left_rotation(t, new_node);
                }

                new_node->parent->color = RBTREE_BLACK;
                new_node->parent->parent->color = RBTREE_RED;
                right_rotation(t, new_node->parent->parent);
            }
        } else {
            uncle_node = new_node->parent->parent->left;

            if(uncle_node->color == RBTREE_RED) {
                new_node->parent->color = RBTREE_BLACK;
                uncle_node->color = RBTREE_BLACK;
                new_node->parent->parent->color = RBTREE_RED;
                new_node = new_node->parent->parent;
            } else {
                if(new_node == new_node->parent->left) {
                    new_node = new_node->parent;
                    right_rotation(t, new_node);
                }

                new_node->parent->color = RBTREE_BLACK;
                new_node->parent->parent->color = RBTREE_RED;
                left_rotation(t, new_node->parent->parent);
            }
        }
    }
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
    node_t *parent_node = t->nil;
    node_t *current_node = t->root;
    node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
    new_node->key = key;

    while(current_node != t->nil) {
        parent_node = current_node;

        if(key < current_node->key) {
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }

    new_node->parent = parent_node;

    if(parent_node == t->nil) {
        t->root = new_node;
    } else if(key < parent_node->key) {
        parent_node->left = new_node;
    } else {
        parent_node->right = new_node;
    }

    new_node->left = new_node->right = t->nil; 
    new_node->color = RBTREE_RED;

    rbtree_insert_fixup(t, new_node);

    t->root->color = RBTREE_BLACK;
    return new_node;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
    node_t *current_node = t->root;

    if (current_node == t->nil) {
        return NULL;
    }
    
    while(current_node != t->nil && current_node->key != key) {
        if(key < current_node->key) {  
            current_node = current_node->left;
        } else {
            current_node = current_node->right;
        }
    }

    if(current_node->key != key) {
        return NULL;
    }

    return current_node;
}

node_t *tree_min(const rbtree *t, node_t *p) {
    node_t *current_node = p;

    while(current_node->left != t->nil) {
        current_node = current_node->left;
    }

    return current_node;
}

node_t *tree_max(const rbtree *t, node_t *p) {
    node_t *current_node = p;

    while(current_node->right != t->nil) {
      current_node = current_node->right;
    }

    return current_node;
}

node_t *rbtree_min(const rbtree *t) {
    return tree_min(t, t->root);
}

node_t *rbtree_max(const rbtree *t) {
    return tree_max(t, t->root);
}

node_t *tree_predecessor(rbtree *t, node_t *x) {
    node_t *parent_node = x;
    node_t *current_node = x->left;

    while(current_node != t->nil) {
        parent_node = current_node;
        current_node = current_node->right;
    }

    return parent_node;
}

void rbtree_erase_fixup(rbtree *t, node_t *current_node) {
    node_t *sibling_node;

    while(current_node != t->root && current_node->color == RBTREE_BLACK) {
        if(current_node == current_node->parent->left) {
            sibling_node = current_node->parent->right;

            if(sibling_node->color == RBTREE_RED) {
                sibling_node->color = RBTREE_BLACK;
                current_node->parent->color = RBTREE_RED;
                left_rotation(t, current_node->parent);
                sibling_node = current_node->parent->right;
            }

            if(sibling_node->left->color == RBTREE_BLACK && sibling_node->right->color == RBTREE_BLACK) {
                sibling_node->color = RBTREE_RED;
                current_node = current_node->parent;
            } else {
                if(sibling_node->right->color == RBTREE_BLACK) {
                    sibling_node->left->color = RBTREE_BLACK;
                    sibling_node->color = RBTREE_RED;
                    right_rotation(t, sibling_node);
                    sibling_node = current_node->parent->right;
                }

                sibling_node->color = current_node->parent->color;
                current_node->parent->color = RBTREE_BLACK;
                sibling_node->right->color = RBTREE_BLACK;
                left_rotation(t, current_node->parent);
                current_node = t->root;
            }
        } else {
            sibling_node = current_node->parent->left;

            if(sibling_node->color == RBTREE_RED) {
                sibling_node->color = RBTREE_BLACK;
                current_node->parent->color = RBTREE_RED;
                right_rotation(t, current_node->parent);
                sibling_node = current_node->parent->left;
            }

            if(sibling_node->right->color == RBTREE_BLACK && sibling_node->left->color == RBTREE_BLACK) {
                sibling_node->color = RBTREE_RED;
                current_node = current_node->parent;
            } else {
                if(sibling_node->left->color == RBTREE_BLACK) {
                    sibling_node->right->color = RBTREE_BLACK;
                    sibling_node->color = RBTREE_RED;
                    left_rotation(t, sibling_node);
                    sibling_node = current_node->parent->left;
                }

                sibling_node->color = current_node->parent->color;
                current_node->parent->color = RBTREE_BLACK;
                sibling_node->left->color = RBTREE_BLACK;
                right_rotation(t, current_node->parent);
                current_node = t->root;
            }
        }
    }
    current_node->color = RBTREE_BLACK;
}

int rbtree_erase(rbtree *t, node_t *p) {
    node_t *delete_child_node, *delete_node;

    if(p->left == t->nil || p->right == t->nil) { 
        delete_node = p;
    } else {
        delete_node = tree_predecessor(t, p);
    }

    if(delete_node->left != t->nil) {
        delete_child_node = delete_node->left;
    } else {
        delete_child_node = delete_node->right;
    }

    delete_child_node->parent = delete_node->parent;

    if(delete_node->parent == t->nil) {
        t->root = delete_child_node;
    } else if(delete_node == delete_node->parent->left) {
        delete_node->parent->left = delete_child_node;
    } else {
        delete_node->parent->right = delete_child_node;
    }

    if(delete_node != p) {
        p->key = delete_node->key;
    }

    if(delete_node->color == RBTREE_BLACK) {
        rbtree_erase_fixup(t, delete_child_node);
    }

    free(delete_node);
    return 0;
}

void inorder_rbtree(const rbtree *t, node_t *current_node, key_t *arr, size_t n, size_t *index) {
    if(current_node == t->nil || *index >= n) {
        return;
    }

    inorder_rbtree(t, current_node->left, arr, n, index);
    arr[(*index)++] = current_node->key;
    inorder_rbtree(t, current_node->right, arr, n, index);
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
    size_t index = 0;

    if(t->root == t-> nil) {
        return 0;
    }
    
    inorder_rbtree(t, t->root, arr, n, &index);
    return 0;
}