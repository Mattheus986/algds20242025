#include "hashtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Простая хеш-функция (djb2)
unsigned int hashFunction(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % TABLE_SIZE;
}

HashTable* createTable() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) return NULL;
    for (int i = 0; i < TABLE_SIZE; i++)
        table->buckets[i] = NULL;
    return table;
}

void freeTable(HashTable* table) {
    if (!table) return;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* curr = table->buckets[i];
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            free(tmp->key);
            free(tmp);
        }
    }
    free(table);
}

void insertKey(HashTable* table, const char* key) {
    if (!table || !key) return;
    unsigned int index = hashFunction(key);

    // проверка на дубликаты
    Node* curr = table->buckets[index];
    while (curr) {
        if (strcmp(curr->key, key) == 0)
            return; // уже есть
        curr = curr->next;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = strdup(key);
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
}

bool searchKey(HashTable* table, const char* key) {
    if (!table || !key) return false;
    unsigned int index = hashFunction(key);
    Node* curr = table->buckets[index];
    while (curr) {
        if (strcmp(curr->key, key) == 0)
            return true;
        curr = curr->next;
    }
    return false;
}

bool removeKey(HashTable* table, const char* key) {
    if (!table || !key) return false;
    unsigned int index = hashFunction(key);
    Node* curr = table->buckets[index];
    Node* prev = NULL;
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            if (prev)
                prev->next = curr->next;
            else
                table->buckets[index] = curr->next;
            free(curr->key);
            free(curr);
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

void printTable(HashTable* table) {
    if (!table) return;
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        Node* curr = table->buckets[i];
        while (curr) {
            printf("%s -> ", curr->key);
            curr = curr->next;
        }
        printf("NULL\n");
    }
}
