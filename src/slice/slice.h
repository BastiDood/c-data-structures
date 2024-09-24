#ifndef SLICE_H
#define SLICE_H

#include <stddef.h>
#include <stdint.h>

void slice_reverse(uint8_t arr[const], size_t len);
void slice_rotate_left(uint8_t arr[const], size_t len, size_t n);
void slice_rotate_right(uint8_t arr[const], size_t len, size_t n);

#endif // SLICE_H
