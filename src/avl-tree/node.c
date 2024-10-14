#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "node.h"

void node_init(struct Node * const self, const size_t data) {
    self->height = 1;
    self->data = data;
    self->left = self->right = NULL;
}

struct Node * node_create(const size_t data) {
    struct Node * const self = malloc(sizeof *self);
    assert(self != NULL);
    node_init(self, data);
    return self;
}

// EXCEPTION: `self` may be `NULL`.
ptrdiff_t node_height(const struct Node * const self) {
    return self == NULL ? 0 : self->height;
}

// EXCEPTION: `self` may be `NULL`.
ptrdiff_t node_balance(const struct Node * const self) {
    return self == NULL ? 0 : node_height(self->right) - node_height(self->left);
}

void node_recompute_height(struct Node * const self) {
    const ptrdiff_t left = node_height(self->left);
    const ptrdiff_t right = node_height(self->right);
    self->height = 1 + max(left, right);
}

struct Node * node_l_rotate(struct Node * const self) {
    struct Node * const other = self->right;
    assert(other != NULL);

    struct Node * const dangling = other->left;
    other->left = self;
    self->right = dangling;

    node_recompute_height(self);
    node_recompute_height(other);
    return other;
}

struct Node * node_r_rotate(struct Node * const self) {
    struct Node * const other = self->left;
    assert(other != NULL);

    struct Node * const dangling = other->right;
    other->right = self;
    self->left = dangling;

    node_recompute_height(self);
    node_recompute_height(other);
    return other;
}

struct Node * node_lr_rotate(struct Node * const self) {
    struct Node * const other = self->left;
    assert(other != NULL);
    self->left = node_l_rotate(other);
    return node_r_rotate(self);
}

struct Node * node_rl_rotate(struct Node * const self) {
    struct Node * const other = self->right;
    assert(other != NULL);
    self->right = node_r_rotate(other);
    return node_l_rotate(self);
}

// EXCEPTION: `self` may be `NULL`.
struct Node * node_insert(struct Node * const self, const size_t data) {
    // Insert at a new empty leaf node
    if (self == NULL) return node_create(data);

    if (data < self->data) self->left = node_insert(self->left, data);
    else if (self->data < data) self->right = node_insert(self->right, data);
    else assert(false); // Duplicate keys are forbidden!

    node_recompute_height(self);
    const ptrdiff_t balance = node_balance(self);

    // Left-heavy
    if (balance < -1) {
        const size_t left = self->left->data;
        if (data < left) return node_r_rotate(self);
        if (left < data) return node_lr_rotate(self);
        assert(false); // Duplicate keys are forbidden!
    }

    // Right-heavy
    if (balance > 1) {
        const size_t right = self->right->data;
        if (data < right) return node_rl_rotate(self);
        if (right < data) return node_l_rotate(self);
        assert(false); // Duplicate keys are forbidden!
    }

    return self;
}
