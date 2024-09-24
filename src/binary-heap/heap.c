#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "heap.h"
#include "slice.h"

void heap_init(struct Heap * const self) {
    self->buf = slice_create_empty();
    self->cap = self->buf.len;
}

struct Heap heap_create(void) {
    struct Heap self;
    heap_init(&self);
    return self;
}

void heap_init_with_capacity(struct Heap * const self, const size_t cap) {
    uint8_t * const data = malloc(cap * sizeof *data);
    assert(data != NULL);
    self->buf = slice_create_valid(data, 0);
    self->cap = cap;
}

struct Heap heap_create_with_capacity(const size_t cap) {
    struct Heap self;
    heap_init_with_capacity(&self, cap);
    return self;
}

void heap_free(struct Heap * const self) {
    free(self->buf.buf);
    heap_init(self);
}

void heap_push(struct Heap * const self, const uint8_t data) {
    // Ensure buffer is already allocated
    if (self->cap == 0) {
        assert(self->buf.len == 0);
        assert(self->buf.buf == NULL);
        heap_init_with_capacity(self, HEAP_DEFAULT_CAPACITY);
    }

    // Resize if necessary
    if (self->buf.len >= self->cap) {
        self->cap *= 2;
        uint8_t * const buf = realloc(self->buf.buf, self->cap * sizeof *buf);
        assert(buf != NULL);
        self->buf.buf = buf;
    }

    // Push data to the correct place
    size_t child = self->buf.len++;
    size_t parent = (child - 1) / 2;
    while (child > 0 && data < self->buf.buf[parent]) {
        // Bubble up the child
        self->buf.buf[child] = self->buf.buf[parent];
        child = parent;
        parent = (child - 1) / 2;
    }
    self->buf.buf[child] = data;
}

// Maintain the min-heap invariant for an almost-heap.
void heapify(struct Heap * const self) {
    const size_t len = self->buf.len;
    if (len == 0) return;

    const uint8_t root = *self->buf.buf;
    size_t parent = 0;
    size_t child = 1;
    while (child < len) {
        // Check if a right child exists
        if (child < len - 1) {
            // Determine whether left or right child is lesser
            const uint8_t left_key = self->buf.buf[child];
            const uint8_t right_key = self->buf.buf[child + 1];
            if (right_key < left_key) ++child;
        }

        // Stop if the parent is already in the right place
        if (root <= self->buf.buf[child]) break;

        // Otherwise, swap with the min-child
        self->buf.buf[parent] = self->buf.buf[child];
        parent = child;
        child = 2 * parent + 1;
    }

    // Finally plop the root where it belongs
    self->buf.buf[parent] = root;
}

uint8_t heap_pop(struct Heap * const self) {
    assert(self->buf.len > 0);

    // Root is always the minimum element
    const uint8_t data = *self->buf.buf;

    // Swap root with the right-most, bottom-most node
    // (which should yield an almost-heap)
    *self->buf.buf = self->buf.buf[--self->buf.len];
    heapify(self);

    return data;
}
