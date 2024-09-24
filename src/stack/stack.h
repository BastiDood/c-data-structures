#ifndef STACK_H
#define STACK_H

#include <stddef.h>
#include <stdint.h>

#include "slice.h"

enum { STACK_DEFAULT_CAPACITY = 4 };

// First-in, last-out collection of bytes.
struct Stack {
    // Underlying buffer.
    struct Slice buf;
    // Current capacity of the internal buffer.
    size_t cap;
};

// Initializes an empty stack without allocating yet.
void stack_init(struct Stack * self);

// Creates an empty stack without allocating yet.
struct Stack stack_create(void);

// Creates a empty heap-allocated stack with the given capacity.
void stack_init_with_capacity(struct Stack * self, size_t cap);

// Creates a empty heap-allocated stack with the given capacity.
struct Stack stack_create_with_capacity(size_t cap);

void stack_free(struct Stack * self);

// Peek at the top of the stack.
uint8_t stack_peek(struct Stack const * self);

// Push an element to the back of the stack.
void stack_push(struct Stack * self, uint8_t item);

// Pop an element off the top of the stack.
uint8_t stack_pop(struct Stack * self);

#endif // !STACK_H
