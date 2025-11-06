#include "bst.h"

BSTNode* bst_create_node(int key) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

BSTNode* bst_insert(BSTNode* root, int key) {
    if (!root) return bst_create_node(key);
    if (key < root->key)
        root->left = bst_insert(root->left, key);
    else if (key > root->key)
        root->right = bst_insert(root->right, key);
    return root;
}

BSTNode* min_bst_node(BSTNode* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

BSTNode* bst_delete(BSTNode* root, int key) {
    if (!root) return NULL;
    if (key < root->key)
        root->left = bst_delete(root->left, key);
    else if (key > root->key)
        root->right = bst_delete(root->right, key);
    else {
        if (!root->left) {
            BSTNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (!root->right) {
            BSTNode* temp = root->left;
            free(root);
            return temp;
        }
        BSTNode* temp = min_bst_node(root->right);
        root->key = temp->key;
        root->right = bst_delete(root->right, temp->key);
    }
    return root;
}

BSTNode* bst_search(BSTNode* root, int key) {
    if (!root || root->key == key)
        return root;
    if (key < root->key)
        return bst_search(root->left, key);
    return bst_search(root->right, key);
}

void bst_free(BSTNode* root) {
    if (!root) return;
    bst_free(root->left);
    bst_free(root->right);
    free(root);
}

void bst_print_inorder(BSTNode* root) {
    if (!root) return;
    bst_print_inorder(root->left);
    printf("%d ", root->key);
    bst_print_inorder(root->right);
}