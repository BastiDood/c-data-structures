#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdint.h>

#define QUEUE_DEFAULT_CAPACITY 4

// First-in, first-out collection of bytes.
struct Queue {
    // Relative index at which we may delete (occupied slot).
    size_t left;
    // Relative index at which we may insert (open slot).
    size_t right;
    // Cached length of the internal buffer.
    size_t len;
    // Total capacity of the internal buffer.
    size_t cap;
    // The underlying buffer.
    uint8_t * buf;
};

// Initializes an empty queue without allocating yet.
void queue_init(struct Queue * self);

// Creates an empty queue without allocating yet.
struct Queue queue_create(void);

// Creates a empty heap-allocated queue with the given capacity.
void queue_init_with_capacity(struct Queue * self, size_t cap);

// Creates a empty heap-allocated queue with the given capacity.
struct Queue queue_create_with_capacity(size_t cap);

void queue_free(struct Queue * self);

// Peeks at the front of the queue.
uint8_t queue_peek(struct Queue const * self);

// Rotate the internal buffer such that `left=0` and `right=len`.
void queue_make_contiguous(struct Queue * self);

// Push a new element to the front of the queue.
size_t queue_push_front(struct Queue * self, uint8_t item);

// Pop an element off the front. Note that the item
// is not deleted from the internal buffer.
uint8_t queue_pop_front(struct Queue * self);

#endif // !QUEUE_H
