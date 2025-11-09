#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>
#include <stddef.h>

#define TABLE_SIZE 10  // размер таблицы можно варьировать

typedef struct Node {
    char* key;
    struct Node* next;
} Node;

typedef struct {
    Node* buckets[TABLE_SIZE];
} HashTable;

// функции работы с таблицей
HashTable* createTable();
void freeTable(HashTable* table);
unsigned int hashFunction(const char* str);
void insertKey(HashTable* table, const char* key);
bool searchKey(HashTable* table, const char* key);
bool removeKey(HashTable* table, const char* key);
void printTable(HashTable* table);

#endif
