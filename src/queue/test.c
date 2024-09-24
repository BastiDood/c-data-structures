#include "queue.h"
#include "unity.h"
#include "unity_internals.h"

void setUp(void) {}

void tearDown(void) {}

void successful_push_and_pop_without_resize(void) {
    struct Queue queue = queue_create_with_capacity(QUEUE_DEFAULT_CAPACITY);

    queue_push_front(&queue, 1);
    queue_push_front(&queue, 2);
    queue_push_front(&queue, 3);
    queue_push_front(&queue, 4);

    TEST_ASSERT_EQUAL(queue.len, 4);
    TEST_ASSERT_EQUAL(queue.cap, 4);

    TEST_ASSERT_EQUAL_UINT8(queue_pop_front(&queue), 1);
    TEST_ASSERT_EQUAL_UINT8(queue_pop_front(&queue), 2);
    TEST_ASSERT_EQUAL_UINT8(queue_pop_front(&queue), 3);
    TEST_ASSERT_EQUAL_UINT8(queue_pop_front(&queue), 4);

    TEST_ASSERT_EQUAL(queue.len, 0);
    TEST_ASSERT_EQUAL(queue.cap, 4);

    queue_free(&queue);
}

void successful_push_and_pop_with_resize(void) {
    struct Queue queue = queue_create_with_capacity(2);

    queue_push_front(&queue, 1);
    queue_push_front(&queue, 2);

    TEST_ASSERT_EQUAL(queue.len, 2);
    TEST_ASSERT_EQUAL(queue.cap, 2);

    queue_push_front(&queue, 1);
    queue_push_front(&queue, 2);

    TEST_ASSERT_EQUAL(queue.len, 4);
    TEST_ASSERT_EQUAL(queue.cap, 4);

    TEST_ASSERT_EQUAL_UINT8(queue_pop_front(&queue), 1);
    TEST_ASSERT_EQUAL_UINT8(queue_pop_front(&queue), 2);

    TEST_ASSERT_EQUAL(queue.len, 2);
    TEST_ASSERT_EQUAL(queue.cap, 4);

    queue_push_front(&queue, 3);

    TEST_ASSERT_EQUAL(queue.len, 3);
    TEST_ASSERT_EQUAL(queue.cap, 4);

    TEST_ASSERT_EQUAL_UINT8(queue_pop_front(&queue), 1);
    TEST_ASSERT_EQUAL_UINT8(queue_pop_front(&queue), 2);
    TEST_ASSERT_EQUAL_UINT8(queue_pop_front(&queue), 3);

    TEST_ASSERT_EQUAL(queue.len, 0);
    TEST_ASSERT_EQUAL(queue.cap, 4);

    queue_free(&queue);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(successful_push_and_pop_without_resize);
    RUN_TEST(successful_push_and_pop_with_resize);
    return UNITY_END();
}
