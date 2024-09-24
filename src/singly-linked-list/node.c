#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "node.h"

void node_init(struct Node * const self, const int data) {
    self->data = data;
    self->next = NULL;
}

struct Node * node_create(const int data) {
    struct Node * self = malloc(sizeof *self);
    assert(self != NULL); // malloc can fail
    node_init(self, data);
    return self;
}

void node_free_chain(struct Node * self) {
    do {
        struct Node * const next = self->next;
        free(self);
        self = next;
    } while (self != NULL);
}

void node_print_chain(const struct Node * self) {
    const int first = printf("%d", self->data);
    assert(first >= 0);

    while (true) {
        self = self->next;
        if (self == NULL) break;
        const int middle = printf(" -> %d", self->data);
        assert(middle >= 0);
    }

    const int last = putchar('\n');
    assert(last >= 0);
}

struct Node * node_swap_chain(struct Node * const self, struct Node * const other) {
    struct Node * const old = self->next;
    self->next = other;
    return old;
}

void node_append(struct Node * const self, struct Node * const other) {
    struct Node * const old = node_swap_chain(self, other);
    if (old != NULL) node_free_chain(old);
}

struct Node * node_get_nth_in_chain(struct Node * self, const size_t n) {
    for (size_t i = 1; i <= n; ++i) {
        struct Node * const next = self->next;
        if (next == NULL) return NULL;
        self = next;
    }
    return self;
}

struct Node * node_get_last_in_chain(struct Node * self) {
    while (true) {
        struct Node * const next = self->next;
        if (next == NULL) break;
        self = next;
    }
    return self;
}

struct Node * node_detect_cycle(struct Node * const self) {
    // Find the meeting point
    struct Node * slow = self;
    struct Node * fast = self;
    do {
        // Traverse once
        if (fast->next == NULL) return NULL;
        fast = fast->next;

        // Traverse twice
        if (fast->next == NULL) return NULL;
        fast = fast->next;

        // Non-null is guaranteed because `fast`
        // has previously traversed this path
        slow = slow->next;
    } while (slow != fast);

    // Trace back to where the cycle starts
    slow = self;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }

    // Returning any of `slow` or `fast` is fine
    return slow;
}
