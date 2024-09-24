#include <stdint.h>

#include "slice.h"
#include "unity.h"
#include "unity_internals.h"

void setUp(void) {}

void tearDown(void) {}

void should_skip_within_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};

    enum { SKIP = 2 };
    struct Slice slice = slice_skip_n(slice_create(bytes, LEN), SKIP);

    uint8_t result[LEN - SKIP] = {2, 3};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(result, slice.buf, slice.len);
}

void should_skip_none(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};
    struct Slice slice = slice_skip_n(slice_create(bytes, LEN), 0);
    TEST_ASSERT_EQUAL_PTR(bytes, slice.buf);
    TEST_ASSERT_EQUAL(LEN, slice.len);
}

void should_skip_at_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};
    struct Slice slice = slice_skip_n(slice_create(bytes, LEN), LEN);
    TEST_ASSERT_EQUAL(0, slice.len);
}

void should_skip_beyond_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};
    struct Slice slice = slice_skip_n(slice_create(bytes, LEN), LEN + 1);
    TEST_ASSERT_EQUAL(0, slice.len);
}

void should_take_none(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};
    struct Slice slice = slice_take_n(slice_create(bytes, LEN), 0);
    TEST_ASSERT_EQUAL(0, slice.len);
}

void should_take_within_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};

    enum { TAKE = 2 };
    struct Slice slice = slice_take_n(slice_create(bytes, LEN), TAKE);

    uint8_t result[LEN - TAKE] = {0, 1};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(result, slice.buf, slice.len);
}

void should_take_at_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};
    struct Slice slice = slice_take_n(slice_create(bytes, LEN), LEN);
    TEST_ASSERT_EQUAL_PTR(bytes, slice.buf);
    TEST_ASSERT_EQUAL(LEN, slice.len);
}

void should_take_beyond_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};
    struct Slice slice = slice_take_n(slice_create(bytes, LEN), LEN + 1);
    TEST_ASSERT_EQUAL_PTR(bytes, slice.buf);
    TEST_ASSERT_EQUAL(LEN, slice.len);
}

void should_reverse(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};

    struct Slice slice = slice_create(bytes, LEN);
    slice_reverse(slice);

    uint8_t result[LEN] = {3, 2, 1, 0};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(result, bytes, LEN);
}

void should_rotate_left_within_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};

    struct Slice slice = slice_create(bytes, LEN);
    slice_rotate_left(slice, 2);

    uint8_t result[LEN] = {2, 3, 0, 1};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(result, bytes, LEN);
}

void should_rotate_left_at_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};

    struct Slice slice = slice_create(bytes, LEN);
    slice_rotate_left(slice, LEN);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(bytes, bytes, LEN);
}

void should_rotate_left_beyond_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};

    struct Slice slice = slice_create(bytes, LEN);
    slice_rotate_left(slice, LEN + 1);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(bytes, bytes, LEN);
}

void should_rotate_right_within_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};

    struct Slice slice = slice_create(bytes, LEN);
    slice_rotate_right(slice, 2);

    uint8_t result[LEN] = {2, 3, 0, 1};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(result, bytes, LEN);
}

void should_rotate_right_at_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};

    struct Slice slice = slice_create(bytes, LEN);
    slice_rotate_right(slice, LEN);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(bytes, bytes, LEN);
}

void should_rotate_right_beyond_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};

    struct Slice slice = slice_create(bytes, LEN);
    slice_rotate_right(slice, LEN + 1);

    uint8_t result[LEN] = {3, 0, 1, 2};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(result, bytes, LEN);
}

int main(void) {
    UNITY_BEGIN();

    // slice_skip_n
    RUN_TEST(should_skip_none);
    RUN_TEST(should_skip_within_length);
    RUN_TEST(should_skip_at_length);
    RUN_TEST(should_skip_beyond_length);

    // slice_take_n
    RUN_TEST(should_take_none);
    RUN_TEST(should_take_within_length);
    RUN_TEST(should_take_at_length);
    RUN_TEST(should_take_beyond_length);

    // slice_reverse
    RUN_TEST(should_reverse);

    // slice_rotate_left
    RUN_TEST(should_rotate_left_within_length);
    RUN_TEST(should_rotate_left_at_length);
    RUN_TEST(should_rotate_left_beyond_length);

    // slice_rotate_right
    RUN_TEST(should_rotate_right_within_length);
    RUN_TEST(should_rotate_right_at_length);
    RUN_TEST(should_rotate_right_beyond_length);

    return UNITY_END();
}
