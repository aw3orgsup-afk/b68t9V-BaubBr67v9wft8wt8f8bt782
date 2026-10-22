#ifndef BST_H
#define BST_H

typedef struct s_btree {
    struct s_btree* left;
    struct s_btree* right;
    int item;
} t_btree;

// Creates a leaf with the given value. Returns NULL on allocation failure.
t_btree* bstree_create_node(int item);

// Inserts a new leaf into a non-empty tree: values with cmpf(item, node) < 0 go left, the rest go right.
void bstree_insert(t_btree* root, int item, int (*cmpf)(int, int));

// Comparator for bstree_insert: negative if a < b, zero if a == b, positive if a > b.
int bstree_compare(int a, int b);

// left subtree -> root -> right subtree
void bstree_apply_infix(t_btree* root, void (*applyf)(int));

// root -> left subtree -> right subtree
void bstree_apply_prefix(t_btree* root, void (*applyf)(int));

// left subtree -> right subtree -> root
void bstree_apply_postfix(t_btree* root, void (*applyf)(int));

// Frees every node of the tree.
void bstree_destroy(t_btree* root);

#endif  // BST_H
