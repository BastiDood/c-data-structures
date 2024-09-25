#include <assert.h>
#include <stddef.h>
#include <stdio.h>

#include "list.h"
#include "node.h"

void list_init(struct List * const self) {
    self->head = self->tail = NULL;
}

struct List list_create(void) {
    struct List list;
    list_init(&list);
    return list;
}

void list_free_forward(struct List * const self) {
    if (self->head != NULL) node_free_chain_forward(self->head);
    list_init(self);
}

void list_free_backward(struct List * const self) {
    if (self->tail != NULL) node_free_chain_backward(self->tail);
    list_init(self);
}

void list_print_forward(const struct List * const self) {
    if (self->head != NULL) {
        node_print_chain_forward(self->head);
        return;
    }
    const int result = puts("*");
    assert(result >= 0);
}

void list_print_backward(const struct List * const self) {
    if (self->tail != NULL) {
        node_print_chain_backward(self->tail);
        return;
    }
    const int result = puts("*");
    assert(result >= 0);
}

void list_push_back_node(struct List * const self, struct Node * const other) {
    if (self->tail == NULL) {
        assert(self->head == NULL);
        self->head = self->tail = other;
        return;
    }
    node_append(self->tail, other);
    self->tail = other;
    if (self->head == NULL) self->head = other;
}

void list_push_back_data(struct List * const self, const int data) {
    list_push_back_node(self, node_create(data));
}

void list_push_front_node(struct List * const self, struct Node * const other) {
    if (self->head == NULL) {
        assert(self->tail == NULL);
        self->head = self->tail = other;
        return;
    }
    node_prepend(self->head, other);
    self->head = other;
    if (self->tail == NULL) self->tail = other;
}

void list_push_front_data(struct List * const self, const int data) {
    list_push_front_node(self, node_create(data));
}
