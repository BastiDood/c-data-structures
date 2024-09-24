#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "node.h"

void node_init(struct Node * const self, const int data) {
    self->data = data;
    self->prev = self->next = NULL;
}

struct Node * node_create(const int data) {
    struct Node * const self = malloc(sizeof *self);
    assert(self != NULL); // malloc can fail
    node_init(self, data);
    return self;
}

void node_free_chain_forward(struct Node * self) {
    do {
        struct Node * const next = self->next;
        free(self);
        self = next;
    } while (self != NULL);
}

void node_free_chain_backward(struct Node * self) {
    do {
        struct Node * const prev = self->prev;
        free(self);
        self = prev;
    } while (self != NULL);
}

void node_print_chain_forward(const struct Node * self) {
    const int first = printf("%d", self->data);
    assert(first >= 0);

    while (true) {
        self = self->next;
        if (self == NULL) break;
        const int middle = printf(" -> %d", self->data);
        assert(middle >= 0);
    }

    const int last = putchar('\n');
    assert(last != EOF);
}

void node_print_chain_backward(const struct Node * self) {
    const int first = printf("%d", self->data);
    assert(first >= 0);

    while (true) {
        self = self->prev;
        if (self == NULL) break;
        const int middle = printf(" -> %d", self->data);
        assert(middle >= 0);
    }

    const int last = putchar('\n');
    assert(last != EOF);
}

void node_append(struct Node * const self, struct Node * const other) {
    if (self->next != NULL) node_free_chain_forward(self->next);
    if (other->prev != NULL) node_free_chain_backward(other->prev);
    self->next = other;
    other->prev = self;
}

void node_prepend(struct Node * const self, struct Node * const other) {
    if (self->prev != NULL) node_free_chain_backward(self->prev);
    if (other->next != NULL) node_print_chain_forward(other->next);
    self->prev = other;
    other->next = self;
}
