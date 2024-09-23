#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// NODE //

// A doubly-linked node (possibly part of a chain).
struct Node {
    int data; // can be any data type you want
    struct Node * prev;
    struct Node * next;
};

// Initializes a node in-place, may it be allocated via the stack or heap.
void node_init(struct Node * const self, const int data) {
    self->data = data;
    self->prev = self->next = NULL;
}

// Initializes a heap-allocated node.
struct Node * node_create(const int data) {
    struct Node * const self = malloc(sizeof *self);
    assert(self != NULL); // malloc can fail
    node_init(self, data);
    return self;
}

// Note that the chain must not contain cycles.
void node_free_chain_forward(struct Node * self) {
    do {
        struct Node * const next = self->next;
        free(self);
        self = next;
    } while (self != NULL);
}

// Note that the chain must not contain cycles.
void node_free_chain_backward(struct Node * self) {
    do {
        struct Node * const prev = self->prev;
        free(self);
        self = prev;
    } while (self != NULL);
}

// Note that the chain must not contain cycles.
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

// Note that the chain must not contain cycles.
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

// Appends `other` to `self` in forward order.
void node_append(struct Node * const self, struct Node * const other) {
    if (self->next != NULL) node_free_chain_forward(self->next);
    if (other->prev != NULL) node_free_chain_backward(other->prev);
    self->next = other;
    other->prev = self;
}

// Prepends `other` to `self` in backward order.
void node_prepend(struct Node * const self, struct Node * const other) {
    if (self->prev != NULL) node_free_chain_backward(self->prev);
    if (other->next != NULL) node_print_chain_forward(other->next);
    self->prev = other;
    other->next = self;
}

// LINKED LIST //

// The list is empty if and only if `head` and `tail` are `NULL`.
struct List {
    struct Node * head;
    struct Node * tail;
};

// Initializes a doubly-linked list in-place.
void list_init(struct List * const self) { self->head = self->tail = NULL; }

// Initializes a stack-allocated doubly-linked list.
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

void list_push_back_data(struct List * const self, const int data) { list_push_back_node(self, node_create(data)); }

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

void list_push_front_data(struct List * const self, const int data) { list_push_front_node(self, node_create(data)); }

// MAIN //

int main(void) {
    struct List list = list_create();
    list_push_back_data(&list, 1);
    list_push_back_data(&list, 2);
    list_push_front_data(&list, 0);

    list_print_forward(&list);
    list_print_backward(&list);

    list_free_forward(&list);
    return EXIT_SUCCESS;
}
