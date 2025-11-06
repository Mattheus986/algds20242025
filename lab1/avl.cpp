#include "avl.h"


AVLNode* avl_create_node(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

int avl_get_height(AVLNode* node) {
    return node ? node->height : 0;
}

int avl_get_balance(AVLNode* node) {
    if (!node) return 0;
    return avl_get_height(node->left) - avl_get_height(node->right);
}

AVLNode* avl_rotate_right(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (avl_get_height(y->left) > avl_get_height(y->right)
        ? avl_get_height(y->left) : avl_get_height(y->right));
    x->height = 1 + (avl_get_height(x->left) > avl_get_height(x->right)
        ? avl_get_height(x->left) : avl_get_height(x->right));

    return x;
}

AVLNode* avl_rotate_left(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (avl_get_height(x->left) > avl_get_height(x->right)
        ? avl_get_height(x->left) : avl_get_height(x->right));
    y->height = 1 + (avl_get_height(y->left) > avl_get_height(y->right)
        ? avl_get_height(y->left) : avl_get_height(y->right));

    return y;
}

AVLNode* avl_insert(AVLNode* root, int key) {
    if (!root) return avl_create_node(key);

    if (key < root->key)
        root->left = avl_insert(root->left, key);
    else if (key > root->key)
        root->right = avl_insert(root->right, key);
    else
        return root;

    root->height = 1 + (avl_get_height(root->left) > avl_get_height(root->right)
        ? avl_get_height(root->left) : avl_get_height(root->right));

    int balance = avl_get_balance(root);

    if (balance > 1 && key < root->left->key)
        return avl_rotate_right(root);

    if (balance < -1 && key > root->right->key)
        return avl_rotate_left(root);

    if (balance > 1 && key > root->left->key) {
        root->left = avl_rotate_left(root->left);
        return avl_rotate_right(root);
    }

    if (balance < -1 && key < root->right->key) {
        root->right = avl_rotate_right(root->right);
        return avl_rotate_left(root);
    }

    return root;
}

AVLNode* min_value_node(AVLNode* node) {
    AVLNode* current = node;
    while (current->left)
        current = current->left;
    return current;
}

AVLNode* avl_delete(AVLNode* root, int key) {
    if (!root) return root;

    if (key < root->key)
        root->left = avl_delete(root->left, key);
    else if (key > root->key)
        root->right = avl_delete(root->right, key);
    else {
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            free(temp);
        }
        else {
            AVLNode* temp = min_value_node(root->right);
            root->key = temp->key;
            root->right = avl_delete(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + (avl_get_height(root->left) > avl_get_height(root->right)
        ? avl_get_height(root->left) : avl_get_height(root->right));

    int balance = avl_get_balance(root);

    if (balance > 1 && avl_get_balance(root->left) >= 0)
        return avl_rotate_right(root);

    if (balance > 1 && avl_get_balance(root->left) < 0) {
        root->left = avl_rotate_left(root->left);
        return avl_rotate_right(root);
    }

    if (balance < -1 && avl_get_balance(root->right) <= 0)
        return avl_rotate_left(root);

    if (balance < -1 && avl_get_balance(root->right) > 0) {
        root->right = avl_rotate_right(root->right);
        return avl_rotate_left(root);
    }

    return root;
}

AVLNode* avl_search(AVLNode* root, int key) {
    if (!root || root->key == key)
        return root;
    if (key < root->key)
        return avl_search(root->left, key);
    return avl_search(root->right, key);
}

void avl_free(AVLNode* root) {
    if (!root) return;
    avl_free(root->left);
    avl_free(root->right);
    free(root);
}

void avl_print_inorder(AVLNode* root) {
    if (!root) return;
    avl_print_inorder(root->left);
    printf("%d ", root->key);
    avl_print_inorder(root->right);
}