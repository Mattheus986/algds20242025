#include <time.h>
#include "avl.h"
#include "bst.h"


void compare_insert_time(int n) {
    clock_t start, end;
    double avl_time, bst_time;

    AVLNode* avl_root = NULL;
    BSTNode* bst_root = NULL;

    start = clock();
    for (int i = 0; i < n; i++) {
        avl_root = avl_insert(avl_root, rand() % 10000);
    }
    end = clock();
    avl_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < n; i++) {
        bst_root = bst_insert(bst_root, rand() % 10000);
    }
    end = clock();
    bst_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Insert %d elements:\n", n);
    printf("AVL: %.6f s, BST: %.6f s\n", avl_time, bst_time);

    avl_free(avl_root);
    bst_free(bst_root);
}