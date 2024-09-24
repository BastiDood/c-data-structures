#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "node.h"

// The list is empty if and only if `head` and `tail` are `NULL`.
struct List {
    struct Node * head;
    struct Node * tail;
};

// Initializes a doubly-linked list in-place.
void list_init(struct List * self);

// Initializes a stack-allocated doubly-linked list.
struct List list_create(void);

void list_free_forward(struct List * self);
void list_free_backward(struct List * self);

void list_print_forward(const struct List * self);
void list_print_backward(const struct List * self);

void list_push_back_node(struct List * self, struct Node * other);
void list_push_back_data(struct List * self, int data);

void list_push_front_node(struct List * self, struct Node * other);
void list_push_front_data(struct List * self, int data);

#endif // !DOUBLY_LINKED_LIST_H
