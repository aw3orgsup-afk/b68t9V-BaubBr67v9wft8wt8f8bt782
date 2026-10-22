#include "bst.h"

#include <stdlib.h>

t_btree* bstree_create_node(int item) {
    t_btree* node = malloc(sizeof(t_btree));
    if (node != NULL) {
        node->item = item;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void bstree_insert(t_btree* root, int item, int (*cmpf)(int, int)) {
    if (root != NULL && cmpf != NULL) {
        t_btree** free_link = NULL;
        t_btree* current = root;
        while (free_link == NULL) {
            t_btree** next = cmpf(item, current->item) < 0 ? &current->left : &current->right;
            if (*next == NULL) {
                free_link = next;
            } else {
                current = *next;
            }
        }
        *free_link = bstree_create_node(item);
    }
}

int bstree_compare(int a, int b) { return (a > b) - (a < b); }

void bstree_apply_infix(t_btree* root, void (*applyf)(int)) {
    if (root != NULL && applyf != NULL) {
        bstree_apply_infix(root->left, applyf);
        applyf(root->item);
        bstree_apply_infix(root->right, applyf);
    }
}

void bstree_apply_prefix(t_btree* root, void (*applyf)(int)) {
    if (root != NULL && applyf != NULL) {
        applyf(root->item);
        bstree_apply_prefix(root->left, applyf);
        bstree_apply_prefix(root->right, applyf);
    }
}

void bstree_apply_postfix(t_btree* root, void (*applyf)(int)) {
    if (root != NULL && applyf != NULL) {
        bstree_apply_postfix(root->left, applyf);
        bstree_apply_postfix(root->right, applyf);
        applyf(root->item);
    }
}

void bstree_destroy(t_btree* root) {
    if (root != NULL) {
        bstree_destroy(root->left);
        bstree_destroy(root->right);
        free(root);
    }
}
