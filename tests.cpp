#include "btree.h"
#include <gtest/gtest.h>
#include <string>
#include <iostream>

TEST(BTreeTest, InsertIntoEmptyTree) {
    BTree* tree = createTree();
    insert(tree, 10);
    testing::internal::CaptureStdout();
    printTree(tree);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("10"), std::string::npos);
    freeTree(tree);
}

TEST(BTreeTest, InsertIncreasing) {
    BTree* tree = createTree();
    for (int i = 1; i <= 5; i++) insert(tree, i);
    testing::internal::CaptureStdout();
    printTree(tree);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("1"), std::string::npos);
    EXPECT_NE(out.find("5"), std::string::npos);
    freeTree(tree);
}

TEST(BTreeTest, InsertDecreasing) {
    BTree* tree = createTree();
    for (int i = 5; i >= 1; i--) insert(tree, i);
    testing::internal::CaptureStdout();
    printTree(tree);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("5"), std::string::npos);
    freeTree(tree);
}

TEST(BTreeTest, PrintEmpty) {
    BTree* tree = createTree();
    testing::internal::CaptureStdout();
    printTree(tree);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("empty"), std::string::npos);
    freeTree(tree);
}

TEST(BTreeTest, SplitWorks) {
    BTree* tree = createTree();
    for (int i = 1; i <= 10; i++) insert(tree, i);
    testing::internal::CaptureStdout();
    printTree(tree);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("10"), std::string::npos);
    freeTree(tree);
}

TEST(BTreeTest, RandomInsertOrder) {
    BTree* tree = createTree();
    int keys[] = { 8, 3, 1, 7, 5, 2, 6, 4 };
    for (int i = 0; i < 8; i++) insert(tree, keys[i]);
    testing::internal::CaptureStdout();
    printTree(tree);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("8"), std::string::npos);
    freeTree(tree);
}

TEST(BTreeTest, SingleElement) {
    BTree* tree = createTree();
    insert(tree, 42);
    testing::internal::CaptureStdout();
    printTree(tree);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("42"), std::string::npos);
    freeTree(tree);
}

TEST(BTreeTest, ManyElements) {
    BTree* tree = createTree();
    for (int i = 0; i < 50; i++) insert(tree, i);
    testing::internal::CaptureStdout();
    printTree(tree);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("49"), std::string::npos);
    freeTree(tree);
}

TEST(BTreeTest, DuplicateInsert) {
    BTree* tree = createTree();
    insert(tree, 5);
    insert(tree, 5);
    testing::internal::CaptureStdout();
    printTree(tree);
    std::string out = testing::internal::GetCapturedStdout();
    EXPECT_NE(out.find("5"), std::string::npos);
    freeTree(tree);
}

TEST(BTreeTest, TreeNotNullAfterInsert) {
    BTree* tree = createTree();
    insert(tree, 1);
    EXPECT_NE(tree->root, nullptr);
    freeTree(tree);
}
