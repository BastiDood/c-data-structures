#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "queue.h"
#include "slice.h"

void queue_init(struct Queue * const self) {
    self->left = self->right = self->cap = self->len = 0;
    self->buf = NULL;
}

struct Queue queue_create(void) {
    struct Queue self;
    queue_init(&self);
    return self;
}

void queue_init_with_capacity(struct Queue * const self, size_t cap) {
    uint8_t * const data = malloc(cap * sizeof *data);
    assert(data != NULL);
    self->buf = data;
    self->cap = cap;
    self->left = self->right = self->len = 0;
}

struct Queue queue_create_with_capacity(const size_t cap) {
    struct Queue self;
    queue_init_with_capacity(&self, cap);
    return self;
}

void queue_free(struct Queue * const self) {
    free(self->buf);
    queue_init(self);
}

uint8_t queue_peek(struct Queue const * const self) {
    assert(self->len > 0);
    return self->buf[self->left];
}

void queue_make_contiguous(struct Queue * const self) {
    slice_rotate_left(slice_create_valid(self->buf, self->cap), self->left);
    self->left = 0;
    self->right = self->len;
}

size_t queue_push_front(struct Queue * const self, const uint8_t item) {
    // Ensure that we have a valid allocation
    if (self->cap == 0) {
        assert(self->buf == NULL);
        assert(self->len == 0);
        assert(self->left == 0);
        assert(self->right == 0);
        queue_init_with_capacity(self, QUEUE_DEFAULT_CAPACITY);
    }

    // Check if we must re-allocate
    if (self->len >= self->cap) {
        queue_make_contiguous(self);
        self->cap *= 2;
        uint8_t * const buf = realloc(self->buf, self->cap * sizeof *buf);
        assert(buf != NULL);
        self->buf = buf;
    }

    // Plop the new element to the end
    self->buf[self->right] = item;
    self->right = (self->right + 1) % self->cap;
    return ++self->len;
}

uint8_t queue_pop_front(struct Queue * const self) {
    assert(self->len > 0);
    const uint8_t byte = self->buf[self->left];
    self->left = (self->left + 1) % self->cap;
    --self->len;
    return byte;
}
