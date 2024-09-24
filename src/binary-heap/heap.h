#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stddef.h>
#include <stdint.h>

#include "slice.h"

enum { HEAP_DEFAULT_CAPACITY = 4 };

// A min-heap.
struct Heap {
    // The underlying buffer.
    struct Slice buf;
    // Maximum number of elements for the buffer allocation.
    size_t cap;
};

// Initializes an empty min-heap without allocating yet.
void heap_init(struct Heap * self);

// Creates an empty heap without allocating yet.
struct Heap heap_create(void);

// Creates a empty heap-allocated heap with the given capacity.
void heap_init_with_capacity(struct Heap * self, size_t cap);

// Creates a empty heap-allocated heap with the given capacity.
struct Heap heap_create_with_capacity(size_t cap);

void heap_free(struct Heap * self);

void heap_push(struct Heap * self, uint8_t data);
uint8_t heap_pop(struct Heap * self);

#endif // !BINARY_HEAP_H
