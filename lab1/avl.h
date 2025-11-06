#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int key;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
} AVLNode;

// Создание нового узла
AVLNode* avl_create_node(int key);

// Основные операции
AVLNode* avl_insert(AVLNode* root, int key);
AVLNode* avl_delete(AVLNode* root, int key);
AVLNode* avl_search(AVLNode* root, int key);

// Вспомогательные функции
int avl_get_height(AVLNode* node);
int avl_get_balance(AVLNode* node);
AVLNode* avl_rotate_left(AVLNode* x);
AVLNode* avl_rotate_right(AVLNode* y);
void avl_free(AVLNode* root);
void avl_print_inorder(AVLNode* root);

#endif