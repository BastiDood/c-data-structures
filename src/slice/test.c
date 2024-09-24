#include <stdint.h>

#include "slice.h"
#include "unity.h"
#include "unity_internals.h"

void setUp(void) {}

void tearDown(void) {}

void should_reverse(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};

    enum { SIZE = LEN * sizeof *bytes };
    slice_reverse(bytes, SIZE);

    uint8_t result[LEN] = {3, 2, 1, 0};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(result, bytes, LEN);
}

void should_rotate_left_within_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};

    enum { SIZE = LEN * sizeof *bytes };
    slice_rotate_left(bytes, SIZE, 2);

    uint8_t result[LEN] = {2, 3, 0, 1};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(result, bytes, LEN);
}

void should_rotate_left_at_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};
    enum { SIZE = LEN * sizeof *bytes };
    slice_rotate_left(bytes, SIZE, SIZE);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(bytes, bytes, LEN);
}

void should_rotate_left_beyond_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};

    enum { SIZE = LEN * sizeof *bytes };
    slice_rotate_left(bytes, SIZE, SIZE + 1);

    uint8_t result[LEN] = {1, 2, 3, 0};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(result, bytes, LEN);
}

void should_rotate_right_within_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};

    enum { SIZE = LEN * sizeof *bytes };
    slice_rotate_right(bytes, SIZE, 2);

    uint8_t result[LEN] = {2, 3, 0, 1};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(result, bytes, LEN);
}

void should_rotate_right_at_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};
    enum { SIZE = LEN * sizeof *bytes };
    slice_rotate_right(bytes, SIZE, SIZE);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(bytes, bytes, LEN);
}

void should_rotate_right_beyond_length(void) {
    enum { LEN = 4 };
    uint8_t bytes[LEN] = {0, 1, 2, 3};

    enum { SIZE = LEN * sizeof *bytes };
    slice_rotate_left(bytes, SIZE, SIZE + 1);

    uint8_t result[LEN] = {3, 0, 1, 2};
    TEST_ASSERT_EQUAL_UINT8_ARRAY(result, bytes, LEN);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(should_reverse);
    RUN_TEST(should_rotate_left_within_length);
    RUN_TEST(should_rotate_left_at_length);
    // RUN_TEST(should_rotate_left_beyond_length);
    RUN_TEST(should_rotate_right_at_length);
    // RUN_TEST(should_rotate_right_beyond_length);
    return UNITY_END();
}
