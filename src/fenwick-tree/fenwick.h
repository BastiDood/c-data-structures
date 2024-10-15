#ifndef FENWICK_H
#define FENWICK_H

#include "slice.h"

struct FenwickTree {
    // Implementation is one-indexed, so the first item is always ignored.
    struct Slice slice;
};

// Initializes a Fenwick tree index in-place. The internal `slice` is modified.
void fenwick_init(struct FenwickTree * self, struct Slice slice);

// Initializes a Fenwick tree index in-place. The internal `slice` is modified.
struct FenwickTree fenwick_create(struct Slice slice);

// Adds `value` to the item currently at index `n`.
void fenwick_add(const struct FenwickTree * self, size_t n, uint8_t value);

// Compute the prefix sum up to index `start` (inclusive).
uint8_t fenwick_prefix_sum(const struct FenwickTree * self, size_t n);

// Compute the range sum `(start, end]`.
uint8_t fenwick_range_sum(const struct FenwickTree * self, size_t start, size_t end);

#endif // !FENWICK_H
