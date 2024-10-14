#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "heap.h"
#include "slice.h"
#include "stack.h"

void heap_init(struct Heap * const self) {
    stack_init(&self->stack);
}

struct Heap heap_create(void) {
    struct Heap self;
    heap_init(&self);
    return self;
}

void heap_init_with_capacity(struct Heap * const self, const size_t cap) {
    stack_init_with_capacity(&self->stack, cap);
}

struct Heap heap_create_with_capacity(const size_t cap) {
    struct Heap self;
    heap_init_with_capacity(&self, cap);
    return self;
}

void heap_free(struct Heap * const self) {
    stack_free(&self->stack);
}

void heap_push(struct Heap * const self, const uint8_t data) {
    // Resize if necessary
    stack_ensure_has_capacity(&self->stack);
    stack_ensure_has_vacancy(&self->stack);

    // Push data to the correct place
    size_t child = self->stack.slice.length++;
    size_t parent = (child - 1) / 2;
    while (child > 0 && data < self->stack.slice.buffer[parent]) {
        // Bubble up the child
        self->stack.slice.buffer[child] = self->stack.slice.buffer[parent];
        child = parent;
        parent = (child - 1) / 2;
    }
    self->stack.slice.buffer[child] = data;
}

uint8_t heap_pop(struct Heap * const self) {
    // Swap root with the right-most, bottom-most node (which should yield an almost-heap)
    const uint8_t root = slice_swap_remove(&self->stack.slice, 0);
    slice_heapify(self->stack.slice);
    return root;
}
