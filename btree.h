#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>
#include <stdio.h>

#define T 2  // минимальная степень B-дерева

typedef struct BTreeNode {
    int keys[2 * T - 1];
    struct BTreeNode* children[2 * T];
    int n;          // количество ключей
    bool leaf;      // true, если лист
} BTreeNode;

typedef struct {
    BTreeNode* root;
} BTree;

// функции для работы с B-деревом
BTreeNode* createNode(bool leaf);
BTree* createTree();
void insert(BTree* tree, int key);
void insertNonFull(BTreeNode* node, int key);
void splitChild(BTreeNode* parent, int i, BTreeNode* y);
void printNode(BTreeNode* node, int level);
void printTree(BTree* tree);
void freeNode(BTreeNode* node);
void freeTree(BTree* tree);

#endif
