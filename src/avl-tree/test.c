#include "avl.h"
#include "unity.h"
#include "unity_internals.h"

void setUp(void) {}

void tearDown(void) {}

void rotate_left(void) {
    struct AvlTree avl = avl_create();
    TEST_ASSERT_NULL(avl.root);

    avl_insert(&avl, 1);
    TEST_ASSERT_EQUAL_UINT(1, avl.root->data);
    TEST_ASSERT_NULL(avl.root->left);
    TEST_ASSERT_NULL(avl.root->right);

    avl_insert(&avl, 2);
    TEST_ASSERT_EQUAL_UINT(1, avl.root->data);
    TEST_ASSERT_EQUAL_UINT(2, avl.root->right->data);
    TEST_ASSERT_NULL(avl.root->left);
    TEST_ASSERT_NULL(avl.root->right->left);
    TEST_ASSERT_NULL(avl.root->right->right);

    avl_insert(&avl, 3);
    TEST_ASSERT_EQUAL_UINT(2, avl.root->data);
    TEST_ASSERT_EQUAL_UINT(1, avl.root->left->data);
    TEST_ASSERT_EQUAL_UINT(3, avl.root->right->data);
    TEST_ASSERT_NULL(avl.root->left->left);
    TEST_ASSERT_NULL(avl.root->left->right);
    TEST_ASSERT_NULL(avl.root->right->left);
    TEST_ASSERT_NULL(avl.root->right->right);
}

void rotate_right(void) {
    struct AvlTree avl = avl_create();
    TEST_ASSERT_NULL(avl.root);

    avl_insert(&avl, 3);
    TEST_ASSERT_EQUAL_UINT(3, avl.root->data);
    TEST_ASSERT_NULL(avl.root->left);
    TEST_ASSERT_NULL(avl.root->right);

    avl_insert(&avl, 2);
    TEST_ASSERT_EQUAL_UINT(3, avl.root->data);
    TEST_ASSERT_EQUAL_UINT(2, avl.root->left->data);
    TEST_ASSERT_NULL(avl.root->right);
    TEST_ASSERT_NULL(avl.root->left->left);
    TEST_ASSERT_NULL(avl.root->left->right);

    avl_insert(&avl, 1);
    TEST_ASSERT_EQUAL_UINT(2, avl.root->data);
    TEST_ASSERT_EQUAL_UINT(1, avl.root->left->data);
    TEST_ASSERT_EQUAL_UINT(3, avl.root->right->data);
    TEST_ASSERT_NULL(avl.root->left->left);
    TEST_ASSERT_NULL(avl.root->left->right);
    TEST_ASSERT_NULL(avl.root->right->left);
    TEST_ASSERT_NULL(avl.root->right->right);
}

void rotate_left_right(void) {
    struct AvlTree avl = avl_create();
    TEST_ASSERT_NULL(avl.root);

    avl_insert(&avl, 3);
    TEST_ASSERT_EQUAL_UINT(3, avl.root->data);
    TEST_ASSERT_NULL(avl.root->left);
    TEST_ASSERT_NULL(avl.root->right);

    avl_insert(&avl, 1);
    TEST_ASSERT_EQUAL_UINT(3, avl.root->data);
    TEST_ASSERT_EQUAL_UINT(1, avl.root->left->data);
    TEST_ASSERT_NULL(avl.root->right);
    TEST_ASSERT_NULL(avl.root->left->left);
    TEST_ASSERT_NULL(avl.root->left->right);

    avl_insert(&avl, 2);
    TEST_ASSERT_EQUAL_UINT(2, avl.root->data);
    TEST_ASSERT_EQUAL_UINT(1, avl.root->left->data);
    TEST_ASSERT_EQUAL_UINT(3, avl.root->right->data);
    TEST_ASSERT_NULL(avl.root->left->left);
    TEST_ASSERT_NULL(avl.root->left->right);
    TEST_ASSERT_NULL(avl.root->right->left);
    TEST_ASSERT_NULL(avl.root->right->right);
}

void rotate_right_left(void) {
    struct AvlTree avl = avl_create();
    TEST_ASSERT_NULL(avl.root);

    avl_insert(&avl, 1);
    TEST_ASSERT_EQUAL_UINT(1, avl.root->data);
    TEST_ASSERT_NULL(avl.root->left);
    TEST_ASSERT_NULL(avl.root->right);

    avl_insert(&avl, 3);
    TEST_ASSERT_EQUAL_UINT(1, avl.root->data);
    TEST_ASSERT_EQUAL_UINT(3, avl.root->right->data);
    TEST_ASSERT_NULL(avl.root->left);
    TEST_ASSERT_NULL(avl.root->right->left);
    TEST_ASSERT_NULL(avl.root->right->right);

    avl_insert(&avl, 2);
    TEST_ASSERT_EQUAL_UINT(2, avl.root->data);
    TEST_ASSERT_EQUAL_UINT(1, avl.root->left->data);
    TEST_ASSERT_EQUAL_UINT(3, avl.root->right->data);
    TEST_ASSERT_NULL(avl.root->left->left);
    TEST_ASSERT_NULL(avl.root->left->right);
    TEST_ASSERT_NULL(avl.root->right->left);
    TEST_ASSERT_NULL(avl.root->right->right);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(rotate_left);
    RUN_TEST(rotate_right);
    RUN_TEST(rotate_left_right);
    RUN_TEST(rotate_right_left);
    return UNITY_END();
}
