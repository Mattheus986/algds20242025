#include <gtest/gtest.h>
#include "avl.h"
#include "bst.h"

// 1. Добавление в пустое дерево
TEST(AVLTest, InsertIntoEmpty_no1) {
    AVLNode* root = NULL;
    root = avl_insert(root, 10);
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->key, 10);
    avl_free(root);
}

// 2. Добавление нескольких элементов
TEST(AVLTest, MultipleInsert_no2) {
    AVLNode* root = NULL;
    root = avl_insert(root, 30);
    root = avl_insert(root, 20);
    root = avl_insert(root, 40);
    root = avl_insert(root, 10);
    ASSERT_NE(avl_search(root, 10), nullptr);
    avl_free(root);
}

// 3. Проверка балансировки
TEST(AVLTest, Balancing_no3) {
    AVLNode* root = NULL;
    root = avl_insert(root, 30);
    root = avl_insert(root, 20);
    root = avl_insert(root, 10); // должно произойти вращение
    ASSERT_EQ(root->key, 20);
    avl_free(root);
}

// 4. Удаление узла без детей
TEST(AVLTest, DeleteLeaf_no4) {
    AVLNode* root = NULL;
    root = avl_insert(root, 10);
    root = avl_delete(root, 10);
    ASSERT_EQ(root, nullptr);
}

// 5. Удаление корня с одним ребенком
TEST(AVLTest, DeleteRootWithChild_no5) {
    AVLNode* root = NULL;
    root = avl_insert(root, 10);
    root = avl_insert(root, 5);
    root = avl_delete(root, 10);
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->key, 5);
    avl_free(root);
}

// 6. Поиск существующего элемента
TEST(AVLTest, SearchExists_no6) {
    AVLNode* root = NULL;
    root = avl_insert(root, 10);
    ASSERT_NE(avl_search(root, 10), nullptr);
    avl_free(root);
}

// 7. Поиск несуществующего элемента
TEST(AVLTest, SearchNotExists_no7) {
    AVLNode* root = NULL;
    root = avl_insert(root, 10);
    ASSERT_EQ(avl_search(root, 5), nullptr);
    avl_free(root);
}

// 8. Проверка корректной работы при множественных удалениях
TEST(AVLTest, MultipleDelete_no8) {
    AVLNode* root = NULL;
    int arr[] = { 10, 20, 30, 40, 50 };
    for (int i = 0; i < 5; i++)
        root = avl_insert(root, arr[i]);
    root = avl_delete(root, 40);
    root = avl_delete(root, 30);
    ASSERT_EQ(avl_search(root, 40), nullptr);
    avl_free(root);
}

// 9. Проверка высоты дерева
TEST(AVLTest, HeightCheck_no9) {
    AVLNode* root = NULL;
    for (int i = 1; i <= 7; i++)
        root = avl_insert(root, i);
    ASSERT_LE(avl_get_height(root), 4);
    avl_free(root);
}

// 10. Сравнение BST и AVL по корректности вставки
TEST(TreeCompare, InsertSame_no10) {
    AVLNode* avl_root = NULL;
    BSTNode* bst_root = NULL;

    int arr[] = { 10, 5, 20 };
    for (int i = 0; i < 3; i++) {
        avl_root = avl_insert(avl_root, arr[i]);
        bst_root = bst_insert(bst_root, arr[i]);
    }

    ASSERT_NE(avl_search(avl_root, 5), nullptr);
    ASSERT_NE(bst_search(bst_root, 5), nullptr);

    avl_free(avl_root);
    bst_free(bst_root);
}

// 11. Удаление корня в BST
TEST(BSTTest, DeleteRoot_no11) {
    BSTNode* root = NULL;
    root = bst_insert(root, 10);
    root = bst_insert(root, 5);
    root = bst_insert(root, 15);
    root = bst_delete(root, 10);
    ASSERT_NE(root, nullptr);
    bst_free(root);
}