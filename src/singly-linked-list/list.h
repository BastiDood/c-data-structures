#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include "node.h"

struct List {
    struct Node * head;
};

// Initializes a singly-linked list in-place.
void list_init(struct List * self);

// Initializes a stack-allocated singly-linked list.
struct List list_create(void);

void list_free(struct List * self);

void list_print(struct List self);

void list_push_front_node(struct List * self, struct Node * node);

void list_push_front_data(struct List * self, int data);

struct Node * list_dequeue(struct List * self);

void list_reverse(struct List * self);

// Plucks the head of the list, leaving `NULL` in its place.
struct Node * list_take(struct List * self);

// Consumes `other` and concats to `self`.
void list_concat(struct List * self, struct List * other);

// Splits the list into two at the index `n`.
// Modifies `self` in-place and returns the second list.
struct List list_split_nth(struct List * self, size_t n);

#endif // !SINGLY_LINKED_LIST_H
