#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "node.h"

void list_init(struct List * const self) {
    self->head = NULL;
}

struct List list_create(void) {
    struct List list;
    list_init(&list);
    return list;
}

void list_free(struct List * const self) {
    if (self->head == NULL) return;
    node_free_chain(self->head);
    list_init(self);
}

void list_print(const struct List self) {
    if (self.head != NULL) {
        node_print_chain(self.head);
        return;
    }
    const int result = puts("*");
    assert(result >= 0);
}

void list_push_front_node(struct List * const self, struct Node * const node) {
    node_append(node, self->head);
    self->head = node;
}

void list_push_front_data(struct List * const self, const int data) {
    list_push_front_node(self, node_create(data));
}

struct Node * list_dequeue(struct List * const self) {
    struct Node * const node = self->head;
    if (node != NULL) {
        self->head = node->next;
        node->next = NULL; // pluck out of the list
    }
    return node;
}

void list_reverse(struct List * const self) {
    struct Node * head = list_dequeue(self);
    if (head == NULL) return;

    while (true) {
        struct Node * const node = list_dequeue(self);
        if (node == NULL) break;
        node_append(node, head); // prepend to head
        head = node;
    }

    self->head = head;
}

struct Node * list_take(struct List * const self) {
    struct Node * const head = self->head;
    list_init(self);
    return head;
}

void list_concat(struct List * const self, struct List * const other) {
    // Simply steal the other head
    if (self->head == NULL) {
        self->head = list_take(other);
        return;
    }

    // Keep dequeueing into `self`
    struct Node * last = node_get_last_in_chain(self->head);
    while (true) {
        struct Node * const node = list_dequeue(other);
        if (node == NULL) break;
        node_append(last, node);
        last = node;
    }
}

struct List list_split_nth(struct List * const self, const size_t n) {
    struct Node * const node = node_get_nth_in_chain(self->head, n);
    struct List list = list_create();
    if (node != NULL) {
        list_push_front_node(&list, node->next);
        node->next = NULL; // break connection
    }
    return list;
}
