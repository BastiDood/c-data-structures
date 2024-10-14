#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stddef.h>

#include "node.h"

struct AvlTree {
    struct Node * root;
};

void avl_init(struct AvlTree * self);
struct AvlTree avl_create();

void avl_insert(struct AvlTree * self, size_t data);

#endif // !AVL_TREE_H
