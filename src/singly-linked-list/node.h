#ifndef SINGLY_LINKED_NODE_H
#define SINGLY_LINKED_NODE_H

#include <stddef.h>

// A singly-linked node (possibly part of a chain).
struct Node {
    int data; // can be any data type you want
    struct Node * next;
};

// Initializes a node in-place, may it be allocated via the stack or heap.
void node_init(struct Node * self, int data);

// Initializes a heap-allocated node.
struct Node * node_create(int data);

// Note that the chain must not contain cycles.
void node_free_chain(struct Node * self);

// Note that the chain must not contain cycles.
void node_print_chain(const struct Node * self);

// Note that `other` can be `NULL` to cut the `self` chain short.
struct Node * node_swap_chain(struct Node * self, struct Node * other);

// Note that `other` can be `NULL` to cut the `self` chain short.
void node_append(struct Node * self, struct Node * other);

struct Node * node_get_nth_in_chain(struct Node * self, size_t n);

struct Node * node_get_last_in_chain(struct Node * self);

// Floyd's Tortoise-and-Hare Algorithm
struct Node * node_detect_cycle(struct Node * self);

#endif // !SINGLY_LINKED_NODE_H
