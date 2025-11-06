#include <stdio.h>
#include "avl.h"
#include "bst.h"

int main() {
    AVLNode* avl_root = NULL;
    BSTNode* bst_root = NULL;

    avl_root = avl_insert(avl_root, 10);
    avl_root = avl_insert(avl_root, 20);
    avl_root = avl_insert(avl_root, 5);

    printf("AVL inorder: ");
    avl_print_inorder(avl_root);
    printf("\n");

    bst_root = bst_insert(bst_root, 10);
    bst_root = bst_insert(bst_root, 20);
    bst_root = bst_insert(bst_root, 5);

    printf("BST inorder: ");
    bst_print_inorder(bst_root);
    printf("\n");

    avl_free(avl_root);
    bst_free(bst_root);
    return 0;
}