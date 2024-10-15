#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

#include "fenwick.h"
#include "slice.h"

// Obtain a mask for the least significant bit of `n` in constant time.
size_t least_significant_bit(const size_t n) {
    return n & -n;
}

void fenwick_init(struct FenwickTree * const self, const struct Slice slice) {
    // Accumulate the range indexes by only adding the current element to their immediate parent
    for (size_t i = 1; i < slice.length; ++i) {
        const size_t direct = i + least_significant_bit(i);
        uint8_t * const parent = slice_try_get(slice, direct);
        if (parent == NULL) continue;
        *parent += slice_get(slice, i);
    }
    self->slice = slice;
}

struct FenwickTree fenwick_create(const struct Slice slice) {
    struct FenwickTree self;
    fenwick_init(&self, slice);
    return self;
}

void fenwick_add(const struct FenwickTree * const self, size_t n, const uint8_t value) {
    assert(n > 0);
    while (n < self->slice.length) {
        uint8_t * const sum = slice_try_get(self->slice, n);
        assert(sum != NULL);
        *sum += value;
        n += least_significant_bit(n);
    }
}

uint8_t fenwick_prefix_sum(const struct FenwickTree * const self, size_t n) {
    uint8_t sum = 0;
    while (n > 0) {
        sum += slice_get(self->slice, n);
        n -= least_significant_bit(n);
    }
    return sum;
}

uint8_t fenwick_range_sum(const struct FenwickTree * const self, const size_t start, const size_t end) {
    assert(start <= end);
    return fenwick_prefix_sum(self, end) - fenwick_prefix_sum(self, start);
}
