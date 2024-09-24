#include "heap.h"
#include "unity.h"
#include "unity_internals.h"

void setUp(void) {}

void tearDown(void) {}

void should_pop_in_ascending_order_when_pushed_ascending_with_resize(void) {
    struct Heap heap = heap_create_with_capacity(2);
    TEST_ASSERT_NOT_NULL(heap.buf.buf);
    TEST_ASSERT_EQUAL(0, heap.buf.len);
    TEST_ASSERT_EQUAL(2, heap.cap);

    heap_push(&heap, 0);
    heap_push(&heap, 1);
    heap_push(&heap, 2);
    heap_push(&heap, 3);

    TEST_ASSERT_EQUAL_UINT8(0, heap_pop(&heap));
    TEST_ASSERT_EQUAL_UINT8(1, heap_pop(&heap));
    TEST_ASSERT_EQUAL_UINT8(2, heap_pop(&heap));
    TEST_ASSERT_EQUAL_UINT8(3, heap_pop(&heap));

    TEST_ASSERT_EQUAL(0, heap.buf.len);
    TEST_ASSERT_EQUAL(4, heap.cap);
}

void should_pop_in_ascending_order_when_pushed_descending_with_resize(void) {
    struct Heap heap = heap_create_with_capacity(2);
    TEST_ASSERT_NOT_NULL(heap.buf.buf);
    TEST_ASSERT_EQUAL(0, heap.buf.len);
    TEST_ASSERT_EQUAL(2, heap.cap);

    heap_push(&heap, 3);
    heap_push(&heap, 2);
    heap_push(&heap, 1);
    heap_push(&heap, 0);

    TEST_ASSERT_EQUAL_UINT8(0, heap_pop(&heap));
    TEST_ASSERT_EQUAL_UINT8(1, heap_pop(&heap));
    TEST_ASSERT_EQUAL_UINT8(2, heap_pop(&heap));
    TEST_ASSERT_EQUAL_UINT8(3, heap_pop(&heap));

    TEST_ASSERT_EQUAL(0, heap.buf.len);
    TEST_ASSERT_EQUAL(4, heap.cap);
}

void should_pop_in_ascending_order_when_pushed_random_with_resize(void) {
    struct Heap heap = heap_create_with_capacity(2);
    TEST_ASSERT_NOT_NULL(heap.buf.buf);
    TEST_ASSERT_EQUAL(0, heap.buf.len);
    TEST_ASSERT_EQUAL(2, heap.cap);

    heap_push(&heap, 2);
    heap_push(&heap, 0);
    heap_push(&heap, 3);
    heap_push(&heap, 1);

    TEST_ASSERT_EQUAL_UINT8(0, heap_pop(&heap));
    TEST_ASSERT_EQUAL_UINT8(1, heap_pop(&heap));
    TEST_ASSERT_EQUAL_UINT8(2, heap_pop(&heap));
    TEST_ASSERT_EQUAL_UINT8(3, heap_pop(&heap));

    TEST_ASSERT_EQUAL(0, heap.buf.len);
    TEST_ASSERT_EQUAL(4, heap.cap);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(should_pop_in_ascending_order_when_pushed_ascending_with_resize);
    RUN_TEST(should_pop_in_ascending_order_when_pushed_descending_with_resize);
    RUN_TEST(should_pop_in_ascending_order_when_pushed_random_with_resize);
    return UNITY_END();
}
