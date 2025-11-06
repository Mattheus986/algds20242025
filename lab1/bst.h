#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode {
    int key;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

BSTNode* bst_create_node(int key);
BSTNode* bst_insert(BSTNode* root, int key);
BSTNode* bst_search(BSTNode* root, int key);
BSTNode* bst_delete(BSTNode* root, int key);
void bst_free(BSTNode* root);
void bst_print_inorder(BSTNode* root);

#endif