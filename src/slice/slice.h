#ifndef SLICE_H
#define SLICE_H

#include <stddef.h>
#include <stdint.h>

struct Slice {
    // A non-null reference to the underlying buffer. Note that
    // this may point to dangling memory when `len` is zero.
    uint8_t * buf;
    size_t len;
};

struct Slice slice_create(uint8_t * buf, size_t len);

// Skips the first `n` elements in the slice.
struct Slice slice_skip_n(struct Slice self, size_t n);

// Takes up to the first `n` elements in the slice.
struct Slice slice_take_n(struct Slice self, size_t n);

void slice_reverse(struct Slice self);
void slice_rotate_left(struct Slice self, size_t n);
void slice_rotate_right(struct Slice self, size_t n);

#endif // SLICE_H
