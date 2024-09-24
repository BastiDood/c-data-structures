#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "node.h"
#include "unity.h"
#include "unity_internals.h"

void setUp(void) {}

void tearDown(void) {}

void should_concatenate(void) {
    struct List a = list_create();
    list_push_front_data(&a, 2);
    list_push_front_data(&a, 1);
    list_push_front_data(&a, 0);
    list_print(a);

    struct List b = list_create();
    list_push_front_data(&b, 5);
    list_push_front_data(&b, 4);
    list_push_front_data(&b, 3);
    list_print(b);

    list_concat(&a, &b);
    list_print(a);
    list_print(b);

    const struct Node * curr = a.head;
    TEST_ASSERT_EQUAL_INT(0, curr->data);

    curr = curr->next;
    TEST_ASSERT_EQUAL_INT(1, curr->data);

    curr = curr->next;
    TEST_ASSERT_EQUAL_INT(2, curr->data);

    curr = curr->next;
    TEST_ASSERT_EQUAL_INT(3, curr->data);

    curr = curr->next;
    TEST_ASSERT_EQUAL_INT(4, curr->data);

    curr = curr->next;
    TEST_ASSERT_EQUAL_INT(5, curr->data);

    curr = curr->next;
    TEST_ASSERT_NULL(curr);

    TEST_ASSERT_NULL(b.head);

    list_free(&a);
    list_free(&b);
}

void should_reverse(void) {
    struct List a = list_create();
    list_push_front_data(&a, 2);
    list_push_front_data(&a, 1);
    list_push_front_data(&a, 0);
    list_print(a);

    list_reverse(&a);
    list_print(a);

    const struct Node * curr = a.head;
    TEST_ASSERT_EQUAL_INT(2, curr->data);

    curr = curr->next;
    TEST_ASSERT_EQUAL_INT(1, curr->data);

    curr = curr->next;
    TEST_ASSERT_EQUAL_INT(0, curr->data);

    curr = curr->next;
    TEST_ASSERT_NULL(curr);

    list_free(&a);
}

void should_detect_no_cycle(void) {
    struct List a = list_create();
    list_push_front_data(&a, 2);
    list_push_front_data(&a, 1);
    list_push_front_data(&a, 0);
    list_print(a);
    TEST_ASSERT_NULL(node_detect_cycle(a.head));
}

void should_detect_cycle(void) {
    struct List cycle = list_create();
    struct Node * const last = node_create(2);
    list_push_front_node(&cycle, last);
    list_push_front_data(&cycle, 1);
    list_push_front_data(&cycle, 0);

    // Artificially induce a cycle
    last->next = cycle.head;
    // TODO: list_print(cycle);

    const struct Node * const node = node_detect_cycle(cycle.head);
    TEST_ASSERT_NOT_NULL(node);
    TEST_ASSERT_EQUAL_INT(0, node->data);

    // Remove the cycle and clean up
    last->next = NULL;
    list_free(&cycle);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(should_concatenate);
    RUN_TEST(should_reverse);
    RUN_TEST(should_detect_no_cycle);
    RUN_TEST(should_detect_cycle);
    return UNITY_END();
}
