#ifndef DOUBLY_LINKED_NODE_H
#define DOUBLY_LINKED_NODE_H

// A doubly-linked node (possibly part of a chain).
struct Node {
    int data; // can be any data type you want
    struct Node * prev;
    struct Node * next;
};

// Initializes a node in-place, may it be allocated via the stack or heap.
void node_init(struct Node * self, int data);

// Initializes a heap-allocated node.
struct Node * node_create(int data);

// Note that the chain must not contain cycles.
void node_free_chain_forward(struct Node * self);

// Note that the chain must not contain cycles.
void node_free_chain_backward(struct Node * self);

// Note that the chain must not contain cycles.
void node_print_chain_forward(const struct Node * self);

// Note that the chain must not contain cycles.
void node_print_chain_backward(const struct Node * self);

// Appends `other` to `self` in forward order.
void node_append(struct Node * self, struct Node * other);

// Prepends `other` to `self` in backward order.
void node_prepend(struct Node * self, struct Node * other);

#endif // !DOUBLY_LINKED_NODE_H
