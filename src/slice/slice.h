#ifndef SLICE_H
#define SLICE_H

#include <stddef.h>
#include <stdint.h>

struct Slice {
    // A non-null reference to the underlying buffer. Note that
    // this may point to dangling memory when `len` is zero.
    uint8_t * buffer;
    size_t length;
};

// Creates a valid slice into `buf`.
struct Slice slice_create_valid(uint8_t * buf, size_t len);

// Creates an empty slice with `buf` set to `NULL`.
struct Slice slice_create_empty(void);

// Skips the first `n` elements in the slice.
struct Slice slice_skip_n(struct Slice self, size_t n);

// Takes up to the first `n` elements in the slice.
struct Slice slice_take_n(struct Slice self, size_t n);

// Checked version of the subscript operator.
uint8_t slice_get(struct Slice self, size_t n);
uint8_t slice_get_first(struct Slice self);
uint8_t slice_get_last(struct Slice self);

// Pops the last element off of this view in-place.
uint8_t slice_pop(struct Slice * self);

void slice_reverse(struct Slice self);
void slice_rotate_left(struct Slice self, size_t n);
void slice_rotate_right(struct Slice self, size_t n);

// Maintain the min-heap invariant for an almost-heap.
void slice_heapify(struct Slice self);

// Removes the element at index `n` in-place and returns it.
// The removed element is replaced by the last element in O(1)
// time. Note that order is not preserved.
uint8_t slice_swap_remove(struct Slice * self, size_t n);

#endif // SLICE_H
