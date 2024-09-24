#include <assert.h>
#include <stddef.h>
#include <stdint.h>

#include "slice.h"

void slice_reverse(uint8_t arr[const], const size_t len) {
    uint8_t * start = arr;
    uint8_t * end = arr + len;
    while (start < --end) {
        const uint8_t temp = *start;
        *(start++) = *end;
        *end = temp;
    }
}

void slice_rotate_left(uint8_t arr[const], const size_t len, size_t n) {
    n %= len; // keep within bounds!
    slice_reverse(arr, n);
    slice_reverse(arr + n, len - n);
    slice_reverse(arr, len);
}

void slice_rotate_right(uint8_t arr[const], const size_t len, size_t n) {
    n %= len; // keep within bounds!
    slice_reverse(arr, len);
    slice_reverse(arr, n);
    slice_reverse(arr + n, len - n);
}
