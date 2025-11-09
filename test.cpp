#include "hashtable.h"
#include <gtest/gtest.h>
#include <string>

TEST(HashTableTest, CreateAndFreeTable) {
    HashTable* table = createTable();
    ASSERT_NE(table, nullptr);
    freeTable(table);
}

TEST(HashTableTest, InsertAndSearchSingle) {
    HashTable* table = createTable();
    insertKey(table, "apple");
    EXPECT_TRUE(searchKey(table, "apple"));
    EXPECT_FALSE(searchKey(table, "banana"));
    freeTable(table);
}

TEST(HashTableTest, InsertMultiple) {
    HashTable* table = createTable();
    insertKey(table, "dog");
    insertKey(table, "cat");
    insertKey(table, "bird");
    EXPECT_TRUE(searchKey(table, "cat"));
    EXPECT_TRUE(searchKey(table, "dog"));
    EXPECT_TRUE(searchKey(table, "bird"));
    EXPECT_FALSE(searchKey(table, "fish"));
    freeTable(table);
}

TEST(HashTableTest, HandleCollisions) {
    HashTable* table = createTable();
    // Подберём строки, которые могут попасть в один bucket
    insertKey(table, "a");
    insertKey(table, "k"); // вероятно в тот же bucket
    EXPECT_TRUE(searchKey(table, "a"));
    EXPECT_TRUE(searchKey(table, "k"));
    freeTable(table);
}

TEST(HashTableTest, RemoveExistingKey) {
    HashTable* table = createTable();
    insertKey(table, "cat");
    EXPECT_TRUE(removeKey(table, "cat"));
    EXPECT_FALSE(searchKey(table, "cat"));
    freeTable(table);
}

TEST(HashTableTest, RemoveNonExistingKey) {
    HashTable* table = createTable();
    insertKey(table, "apple");
    EXPECT_FALSE(removeKey(table, "banana"));
    freeTable(table);
}

TEST(HashTableTest, DuplicateInsert) {
    HashTable* table = createTable();
    insertKey(table, "test");
    insertKey(table, "test");
    int count = 0;
    unsigned int index = hashFunction("test");
    Node* node = table->buckets[index];
    while (node) {
        if (strcmp(node->key, "test") == 0) count++;
        node = node->next;
    }
    EXPECT_EQ(count, 1);
    freeTable(table);
}

TEST(HashTableTest, RemoveMiddleOfChain) {
    HashTable* table = createTable();
    insertKey(table, "a");
    insertKey(table, "k");
    insertKey(table, "u");
    EXPECT_TRUE(removeKey(table, "k"));
    EXPECT_FALSE(searchKey(table, "k"));
    freeTable(table);
}

TEST(HashTableTest, InsertEmptyString) {
    HashTable* table = createTable();
    insertKey(table, "");
    EXPECT_TRUE(searchKey(table, ""));
    freeTable(table);
}

TEST(HashTableTest, PrintTableOutput) {
    HashTable* table = createTable();
    insertKey(table, "apple");
    testing::internal::CaptureStdout();
    printTable(table);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("apple"), std::string::npos);
    freeTable(table);
}
