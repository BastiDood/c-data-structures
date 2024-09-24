#include "list.h"
#include "node.h"
#include "unity.h"
#include "unity_internals.h"

void setUp(void) {}

void tearDown(void) {}

void should_push_front_and_back(void) {
    struct List list = list_create();
    list_push_back_data(&list, 1);
    list_push_back_data(&list, 2);
    list_push_front_data(&list, 0);

    const struct Node * curr = list.head;
    TEST_ASSERT_EQUAL_INT(0, curr->data);

    curr = curr->next;
    TEST_ASSERT_EQUAL_INT(1, curr->data);

    curr = curr->next;
    TEST_ASSERT_EQUAL_INT(2, curr->data);

    curr = curr->next;
    TEST_ASSERT_NULL(curr);

    list_print_forward(&list);
    list_print_backward(&list);
    list_free_forward(&list);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(should_push_front_and_back);
    return UNITY_END();
}
