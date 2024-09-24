#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "slice.h"

struct Slice slice_create(uint8_t * const buf, const size_t len) { return (struct Slice){.buf = buf, .len = len}; }

struct Slice slice_skip_n(const struct Slice self, const size_t n) {
    const size_t len = self.len < n ? 0 : self.len - n;
    return (struct Slice){.buf = self.buf + n, .len = len};
}

struct Slice slice_take_n(const struct Slice self, const size_t n) {
    const size_t len = self.len < n ? self.len : n;
    return (struct Slice){.buf = self.buf, .len = len};
}

void slice_reverse(const struct Slice self) {
    uint8_t * start = self.buf;
    uint8_t * end = self.buf + self.len;
    while (start < --end) {
        const uint8_t temp = *start;
        *(start++) = *end;
        *end = temp;
    }
}

void slice_rotate_left(const struct Slice self, size_t n) {
    n %= self.len; // keep within bounds!
    slice_reverse(slice_take_n(self, n));
    slice_reverse(slice_skip_n(self, n));
    slice_reverse(self);
}

void slice_rotate_right(const struct Slice self, size_t n) {
    n %= self.len; // keep within bounds!
    slice_reverse(self);
    slice_reverse(slice_take_n(self, n));
    slice_reverse(slice_skip_n(self, n));
}
