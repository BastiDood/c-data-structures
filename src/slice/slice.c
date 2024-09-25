#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "slice.h"

struct Slice slice_create_valid(uint8_t * const buf, const size_t len) {
    return (struct Slice){.buffer = buf, .length = len};
}

struct Slice slice_create_empty(void) {
    return slice_create_valid(NULL, 0);
}

struct Slice slice_skip_n(const struct Slice self, const size_t n) {
    const size_t len = self.length < n ? 0 : self.length - n; // clamp above zero
    return (struct Slice){.buffer = self.buffer + n, .length = len};
}

struct Slice slice_take_n(const struct Slice self, const size_t n) {
    const size_t len = self.length < n ? self.length : n; // clamp below length
    return (struct Slice){.buffer = self.buffer, .length = len};
}

uint8_t * slice_try_get(const struct Slice self, const size_t n) {
    return n < self.length ? self.buffer + n : NULL;
}

uint8_t slice_get(const struct Slice self, size_t n) {
    const uint8_t * const byte = slice_try_get(self, n);
    assert(byte != NULL);
    return *byte;
}

uint8_t slice_get_first(const struct Slice self) {
    return slice_get(self, 0);
}

uint8_t slice_get_last(const struct Slice self) {
    assert(self.length > 0); // underflow guard
    return slice_get(self, self.length - 1);
}

uint8_t slice_pop(struct Slice * const self) {
    assert(self->length > 0);
    return self->buffer[--self->length];
}

void slice_reverse(const struct Slice self) {
    uint8_t * start = self.buffer;
    uint8_t * end = self.buffer + self.length;
    while (start < --end) {
        const uint8_t temp = *start;
        *(start++) = *end;
        *end = temp;
    }
}

void slice_rotate_left(const struct Slice self, size_t n) {
    n %= self.length; // keep within bounds!
    slice_reverse(slice_take_n(self, n));
    slice_reverse(slice_skip_n(self, n));
    slice_reverse(self);
}

void slice_rotate_right(const struct Slice self, size_t n) {
    n %= self.length; // keep within bounds!
    slice_reverse(self);
    slice_reverse(slice_take_n(self, n));
    slice_reverse(slice_skip_n(self, n));
}

void slice_heapify(const struct Slice self) {
    const uint8_t * const first = slice_try_get(self, 0);
    if (first == NULL) return;

    const uint8_t root = *first;
    size_t parent = 0;
    size_t child = 1;
    while (child < self.length) {
        // Check if a right child exists
        if (child < self.length - 1) {
            // Determine whether left or right child is lesser
            const uint8_t left_key = self.buffer[child];
            const uint8_t right_key = self.buffer[child + 1];
            if (right_key < left_key) ++child;
        }

        // Stop if the parent is already in the right place
        if (root <= self.buffer[child]) break;

        // Otherwise, swap with the min-child
        self.buffer[parent] = self.buffer[child];
        parent = child;
        child = 2 * parent + 1;
    }

    // Finally plop the root to where it belongs
    self.buffer[parent] = root;
}

uint8_t slice_swap_remove(struct Slice * const self, const size_t n) {
    const uint8_t root = slice_get(*self, n);
    self->buffer[n] = self->buffer[--self->length];
    return root;
}
