#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "slice.h"
#include "stack.h"

void stack_init(struct Stack * const self) {
    self->slice = slice_create_empty();
    self->capacity = self->slice.length;
}

struct Stack stack_create(void) {
    struct Stack self;
    stack_init(&self);
    return self;
}

void stack_init_with_capacity(struct Stack * const self, const size_t cap) {
    uint8_t * const data = malloc(cap * sizeof *data);
    assert(data != NULL);
    self->slice = slice_create_valid(data, 0);
    self->capacity = cap;
}

struct Stack stack_create_with_capacity(const size_t cap) {
    struct Stack self;
    stack_init_with_capacity(&self, cap);
    return self;
}

void stack_increase_capacity(struct Stack * const self, const size_t len) {
    self->capacity += len;
    uint8_t * const buf = realloc(self->slice.buffer, self->capacity * sizeof *buf);
    assert(buf != NULL);
    self->slice.buffer = buf;
}

void stack_ensure_has_capacity(struct Stack * self) {
    if (self->capacity > 0) return;
    assert(self->slice.buffer == NULL);
    assert(self->slice.length == 0);
    stack_init_with_capacity(self, STACK_DEFAULT_CAPACITY);
}

bool stack_has_vacancy(const struct Stack * const self) {
    return self->slice.length < self->capacity;
}

void stack_ensure_has_vacancy(struct Stack * self) {
    if (stack_has_vacancy(self)) return;
    stack_increase_capacity(self, self->capacity);
}

void stack_free(struct Stack * const self) {
    free(self->slice.buffer);
    stack_init(self);
}

uint8_t stack_peek(struct Stack const * const self) {
    return slice_get_last(self->slice);
}

void stack_push(struct Stack * const self, const uint8_t item) {
    // Resize if necessary
    stack_ensure_has_capacity(self);
    stack_ensure_has_vacancy(self);

    // Push new item
    self->slice.buffer[self->slice.length++] = item;
}

uint8_t stack_pop(struct Stack * const self) {
    return slice_pop(&self->slice);
}
