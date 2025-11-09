#include "btree.h"
#include <stdlib.h>

BTreeNode* createNode(bool leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->leaf = leaf;
    node->n = 0;
    for (int i = 0; i < 2 * T; ++i)
        node->children[i] = NULL;
    return node;
}

BTree* createTree() {
    BTree* tree = (BTree*)malloc(sizeof(BTree));
    tree->root = NULL;
    return tree;
}

void splitChild(BTreeNode* parent, int i, BTreeNode* y) {
    BTreeNode* z = createNode(y->leaf);
    z->n = T - 1;

    // копируем правую половину ключей
    for (int j = 0; j < T - 1; j++)
        z->keys[j] = y->keys[j + T];

    // копируем детей
    if (!y->leaf) {
        for (int j = 0; j < T; j++)
            z->children[j] = y->children[j + T];
    }

    y->n = T - 1;

    for (int j = parent->n; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];
    parent->children[i + 1] = z;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];
    parent->keys[i] = y->keys[T - 1];
    parent->n++;
}

void insertNonFull(BTreeNode* node, int key) {
    int i = node->n - 1;

    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    }
    else {
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;
        if (node->children[i]->n == 2 * T - 1) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i])
                i++;
        }
        insertNonFull(node->children[i], key);
    }
}

void insert(BTree* tree, int key) {
    if (tree->root == NULL) {
        tree->root = createNode(true);
        tree->root->keys[0] = key;
        tree->root->n = 1;
        return;
    }

    if (tree->root->n == 2 * T - 1) {
        BTreeNode* s = createNode(false);
        s->children[0] = tree->root;
        splitChild(s, 0, tree->root);

        int i = 0;
        if (key > s->keys[0])
            i++;
        insertNonFull(s->children[i], key);
        tree->root = s;
    }
    else {
        insertNonFull(tree->root, key);
    }
}

void printNode(BTreeNode* node, int level) {
    for (int i = 0; i < level; i++)
        printf("  ");

    for (int i = 0; i < node->n; i++)
        printf("%d ", node->keys[i]);
    printf("\n");

    if (!node->leaf) {
        for (int i = 0; i <= node->n; i++)
            if (node->children[i])
                printNode(node->children[i], level + 1);
    }
}

void printTree(BTree* tree) {
    if (tree->root)
        printNode(tree->root, 0);
    else
        printf("(empty tree)\n");
}

void freeNode(BTreeNode* node) {
    if (!node) return;
    if (!node->leaf) {
        for (int i = 0; i <= node->n; i++)
            freeNode(node->children[i]);
    }
    free(node);
}

void freeTree(BTree* tree) {
    if (!tree) return;
    freeNode(tree->root);
    free(tree);
}
