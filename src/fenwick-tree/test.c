#include "fenwick.h"
#include "slice.h"
#include "unity.h"
#include "unity_internals.h"

void setUp(void) {}

void tearDown(void) {}

void prefix_sums_power_of_two_length(void) {
    uint8_t bytes[9] = {0, 1, 5, 8, 2, 0, 8, 9, 3}; // 0th is unused
    const struct FenwickTree fenwick = fenwick_create(slice_create_valid(bytes, 9));
    TEST_ASSERT_EQUAL_UINT(0, fenwick_prefix_sum(&fenwick, 0));
    TEST_ASSERT_EQUAL_UINT(1, fenwick_prefix_sum(&fenwick, 1));
    TEST_ASSERT_EQUAL_UINT(6, fenwick_prefix_sum(&fenwick, 2));
    TEST_ASSERT_EQUAL_UINT(14, fenwick_prefix_sum(&fenwick, 3));
    TEST_ASSERT_EQUAL_UINT(16, fenwick_prefix_sum(&fenwick, 4));
    TEST_ASSERT_EQUAL_UINT(16, fenwick_prefix_sum(&fenwick, 5));
    TEST_ASSERT_EQUAL_UINT(24, fenwick_prefix_sum(&fenwick, 6));
    TEST_ASSERT_EQUAL_UINT(33, fenwick_prefix_sum(&fenwick, 7));
    TEST_ASSERT_EQUAL_UINT(36, fenwick_prefix_sum(&fenwick, 8));
}

void prefix_sums_non_power_of_two_length(void) {
    uint8_t bytes[7] = {0, 6, 3, 9, 4, 10, 8}; // 0th is unused
    const struct FenwickTree fenwick = fenwick_create(slice_create_valid(bytes, 7));
    TEST_ASSERT_EQUAL_UINT(0, fenwick_prefix_sum(&fenwick, 0));
    TEST_ASSERT_EQUAL_UINT(6, fenwick_prefix_sum(&fenwick, 1));
    TEST_ASSERT_EQUAL_UINT(9, fenwick_prefix_sum(&fenwick, 2));
    TEST_ASSERT_EQUAL_UINT(18, fenwick_prefix_sum(&fenwick, 3));
    TEST_ASSERT_EQUAL_UINT(22, fenwick_prefix_sum(&fenwick, 4));
    TEST_ASSERT_EQUAL_UINT(32, fenwick_prefix_sum(&fenwick, 5));
    TEST_ASSERT_EQUAL_UINT(40, fenwick_prefix_sum(&fenwick, 6));
}

void range_sums_power_of_two_length(void) {
    uint8_t bytes[9] = {0, 1, 5, 8, 2, 0, 8, 9, 3}; // 0th is unused
    const struct FenwickTree fenwick = fenwick_create(slice_create_valid(bytes, 9));
    TEST_ASSERT_EQUAL_UINT(35, fenwick_range_sum(&fenwick, 1, 8));
    TEST_ASSERT_EQUAL_UINT(15, fenwick_range_sum(&fenwick, 1, 4));
    TEST_ASSERT_EQUAL_UINT(17, fenwick_range_sum(&fenwick, 5, 7));
    TEST_ASSERT_EQUAL_UINT(20, fenwick_range_sum(&fenwick, 4, 8));
}

void range_sums_non_power_of_two_length(void) {
    uint8_t bytes[5] = {0, 1, 5, 8, 2}; // 0th is unused
    const struct FenwickTree fenwick = fenwick_create(slice_create_valid(bytes, 5));
    TEST_ASSERT_EQUAL_UINT(5, fenwick_range_sum(&fenwick, 1, 2));
    TEST_ASSERT_EQUAL_UINT(13, fenwick_range_sum(&fenwick, 1, 3));
    TEST_ASSERT_EQUAL_UINT(15, fenwick_range_sum(&fenwick, 1, 4));
    TEST_ASSERT_EQUAL_UINT(8, fenwick_range_sum(&fenwick, 2, 3));
    TEST_ASSERT_EQUAL_UINT(10, fenwick_range_sum(&fenwick, 2, 4));
    TEST_ASSERT_EQUAL_UINT(2, fenwick_range_sum(&fenwick, 3, 4));
}

void update_tree_tests(void) {
    uint8_t bytes[9] = {0, 1, 5, 8, 2, 0, 8, 9, 3}; // 0th is unused
    const struct FenwickTree fenwick = fenwick_create(slice_create_valid(bytes, 9));
    TEST_ASSERT_EQUAL_UINT(15, fenwick_range_sum(&fenwick, 1, 4));
    TEST_ASSERT_EQUAL_UINT(22, fenwick_range_sum(&fenwick, 3, 8));

    fenwick_add(&fenwick, 2, 8);
    TEST_ASSERT_EQUAL_UINT(23, fenwick_range_sum(&fenwick, 1, 4));
    TEST_ASSERT_EQUAL_UINT(22, fenwick_range_sum(&fenwick, 3, 8));

    fenwick_add(&fenwick, 5, 1);
    TEST_ASSERT_EQUAL_UINT(23, fenwick_range_sum(&fenwick, 1, 4));
    TEST_ASSERT_EQUAL_UINT(23, fenwick_range_sum(&fenwick, 3, 8));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(prefix_sums_power_of_two_length);
    RUN_TEST(prefix_sums_non_power_of_two_length);
    RUN_TEST(range_sums_power_of_two_length);
    RUN_TEST(range_sums_non_power_of_two_length);
    RUN_TEST(update_tree_tests);
    return UNITY_END();
}
