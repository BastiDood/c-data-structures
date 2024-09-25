#include "stack.h"
#include "unity.h"
#include "unity_internals.h"

void setUp(void) {}

void tearDown(void) {}

void successful_push_and_pop_without_resize(void) {
    struct Stack stack = stack_create_with_capacity(STACK_DEFAULT_CAPACITY);

    stack_push(&stack, 1);
    stack_push(&stack, 2);
    stack_push(&stack, 3);
    stack_push(&stack, 4);

    TEST_ASSERT_EQUAL(stack.slice.length, 4);
    TEST_ASSERT_EQUAL(stack.capacity, 4);

    TEST_ASSERT_EQUAL_UINT8(4, stack_pop(&stack));
    TEST_ASSERT_EQUAL_UINT8(3, stack_pop(&stack));
    TEST_ASSERT_EQUAL_UINT8(2, stack_pop(&stack));
    TEST_ASSERT_EQUAL_UINT8(1, stack_pop(&stack));

    TEST_ASSERT_EQUAL(stack.slice.length, 0);
    TEST_ASSERT_EQUAL(stack.capacity, 4);

    stack_free(&stack);
    TEST_ASSERT_NULL(stack.slice.buffer);
}

void successful_push_and_pop_with_resize(void) {
    struct Stack stack = stack_create_with_capacity(2);

    stack_push(&stack, 1);
    stack_push(&stack, 2);

    TEST_ASSERT_EQUAL(stack.slice.length, 2);
    TEST_ASSERT_EQUAL(stack.capacity, 2);

    stack_push(&stack, 1);
    stack_push(&stack, 2);

    TEST_ASSERT_EQUAL(stack.slice.length, 4);
    TEST_ASSERT_EQUAL(stack.capacity, 4);

    TEST_ASSERT_EQUAL_UINT8(2, stack_pop(&stack));
    TEST_ASSERT_EQUAL_UINT8(1, stack_pop(&stack));
    TEST_ASSERT_EQUAL_UINT8(2, stack_pop(&stack));
    TEST_ASSERT_EQUAL_UINT8(1, stack_pop(&stack));

    TEST_ASSERT_EQUAL(stack.slice.length, 0);
    TEST_ASSERT_EQUAL(stack.capacity, 4);

    stack_free(&stack);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(successful_push_and_pop_without_resize);
    RUN_TEST(successful_push_and_pop_with_resize);
    return UNITY_END();
}
