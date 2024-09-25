#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "slice.h"
#include "stack.h"

void stack_init(struct Stack * const self) {
    self->buf = slice_create_empty();
    self->cap = self->buf.len;
}

struct Stack stack_create(void) {
    struct Stack self;
    stack_init(&self);
    return self;
}

void stack_init_with_capacity(struct Stack * const self, const size_t cap) {
    uint8_t * const data = malloc(cap * sizeof *data);
    assert(data != NULL);
    self->buf = slice_create_valid(data, 0);
    self->cap = cap;
}

struct Stack stack_create_with_capacity(const size_t cap) {
    struct Stack self;
    stack_init_with_capacity(&self, cap);
    return self;
}

void stack_free(struct Stack * const self) {
    free(self->buf.buf);
    stack_init(self);
}

uint8_t stack_peek(struct Stack const * const self) {
    return slice_get_last(self->buf);
}

void stack_increase_capacity(struct Stack * const self, const size_t len) {
    self->cap += len;
    uint8_t * const buf = realloc(self->buf.buf, self->cap * sizeof *buf);
    assert(buf != NULL);
    self->buf.buf = buf;
}

void stack_push(struct Stack * const self, const uint8_t item) {
    // Ensure that the buffer has been allocated
    if (self->cap == 0) {
        assert(self->buf.len == 0);
        assert(self->buf.buf == NULL);
        stack_init_with_capacity(self, STACK_DEFAULT_CAPACITY);
    }

    // Resize if necessary
    if (self->buf.len >= self->cap) stack_increase_capacity(self, self->cap);

    // Push new item
    self->buf.buf[self->buf.len++] = item;
}

uint8_t stack_pop(struct Stack * const self) {
    return slice_pop(&self->buf);
}
