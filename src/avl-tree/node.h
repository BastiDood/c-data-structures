#ifndef AVL_NODE_H
#define AVL_NODE_H

#include <stddef.h>
#include <stdint.h>

struct Node {
    size_t data;
    ptrdiff_t height;
    struct Node * left;
    struct Node * right;
};

void node_init(struct Node * self, size_t data);
struct Node * node_create(size_t data);

// EXCEPTION: `self` may be `NULL`.
ptrdiff_t node_height(const struct Node * self);

// EXCEPTION: `self` may be `NULL`.
ptrdiff_t node_balance(const struct Node * self);

struct Node * node_l_rotate(struct Node * self);
struct Node * node_r_rotate(struct Node * self);
struct Node * node_lr_rotate(struct Node * self);
struct Node * node_rl_rotate(struct Node * self);

// EXCEPTION: `self` may be `NULL`.
struct Node * node_insert(struct Node * self, size_t data);

#endif // !AVL_NODE_H
