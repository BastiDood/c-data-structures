#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// NODE //

// A singly-linked node (possibly part of a chain).
struct Node {
    int data; // can be any data type you want
    struct Node * next;
};

// Initializes a node in-place, may it be allocated via the stack or heap.
void node_init(struct Node * const self, const int data) {
    self->data = data;
    self->next = NULL;
}

// Initializes a heap-allocated node.
struct Node * node_create(const int data) {
    struct Node * self = malloc(sizeof *self);
    assert(self != NULL); // malloc can fail
    node_init(self, data);
    return self;
}

// Note that the chain must not contain cycles.
void node_free_chain(struct Node * self) {
    do {
        struct Node * const next = self->next;
        free(self);
        self = next;
    } while (self != NULL);
}

// Note that the chain must not contain cycles.
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

// Note that `other` can be `NULL` to cut the `self` chain short.
struct Node * node_swap_chain(struct Node * const self, struct Node * const other) {
    struct Node * const old = self->next;
    self->next = other;
    return old;
}

// Note that `other` can be `NULL` to cut the `self` chain short.
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

// Floyd's Tortoise-and-Hare Algorithm
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

// LINKED LIST //

struct List {
    struct Node * head;
};

// Initializes a singly-linked list in-place.
void list_init(struct List * const self) { self->head = NULL; }

// Initializes a stack-allocated singly-linked list.
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

void list_push_front_data(struct List * const self, const int data) { list_push_front_node(self, node_create(data)); }

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

// Plucks the head of the list, leaving `NULL` in its place.
struct Node * list_take(struct List * const self) {
    struct Node * const head = self->head;
    list_init(self);
    return head;
}

// Consumes `other` and concats to `self`.
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

// MAIN //

int main(void) {
    struct List a = list_create();
    list_push_front_data(&a, 2);
    list_push_front_data(&a, 1);
    list_push_front_data(&a, 0);
    list_print(a);
    printf("%p\n", (void *)node_detect_cycle(a.head));

    struct List b = list_create();
    list_push_front_data(&b, 5);
    list_push_front_data(&b, 4);
    list_push_front_data(&b, 3);
    list_print(b);
    printf("%p\n", (void *)node_detect_cycle(b.head));

    list_concat(&a, &b);
    list_print(a);
    list_print(b);

    list_reverse(&a);
    list_print(a);

    list_free(&a);
    list_free(&b);

    struct List cycle = list_create();
    struct Node * const last = node_create(2);
    list_push_front_node(&cycle, last);
    list_push_front_data(&cycle, 1);
    list_push_front_data(&cycle, 0);
    last->next = cycle.head;
    // TODO: list_print(cycle);

    printf("%d\n", node_detect_cycle(cycle.head)->data);

    last->next = NULL;
    list_free(&cycle);

    return EXIT_SUCCESS;
}
