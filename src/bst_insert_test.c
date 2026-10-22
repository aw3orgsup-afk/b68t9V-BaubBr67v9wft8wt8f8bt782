#include <stdio.h>
#include <string.h>

#include "bst.h"

#define SUCCESS 0
#define FAIL 1
#define MAX_PATH_LENGTH 32

static int test_insert_set(const char* name, const int* items, const char* const* expected_paths, int count);
static int test_modules_set(void);
static int test_ascending_set(void);
static int test_duplicates_set(void);
static int test_invalid_arguments(void);
static const t_btree* trace_insertion(const t_btree* root, int item, char* path);
static void print_location(const t_btree* root, const char* path);

int main(void) {
    int failed = 0;
    failed += test_modules_set() == FAIL;
    failed += test_ascending_set() == FAIL;
    failed += test_duplicates_set() == FAIL;
    failed += test_invalid_arguments() == FAIL;
    return failed > 0;
}

// Expected paths: 'L' - go to the left child, 'R' - go to the right child, "" - root
static int test_modules_set(void) {
    const int items[] = {4, 2, 8, 1, 3, 6, 9, 0, 5, 7, 10};
    const char* const paths[] = {"", "L", "R", "LL", "LR", "RL", "RR", "LLL", "RLL", "RLR", "RRR"};
    return test_insert_set("Set 1 (modules 0..10, documentation module 4 is the root)", items, paths, 11);
}

static int test_ascending_set(void) {
    const int items[] = {1, 2, 3, 4, 5};
    const char* const paths[] = {"", "R", "RR", "RRR", "RRRR"};
    return test_insert_set("Set 2 (ascending values, degenerate tree)", items, paths, 5);
}

// Equal values go to the right subtree
static int test_duplicates_set(void) {
    const int items[] = {0, -5, 5, -5, 0, 3};
    const char* const paths[] = {"", "L", "R", "LR", "RL", "RLR"};
    return test_insert_set("Set 3 (negative and repeated values)", items, paths, 6);
}

// Builds a tree item by item and checks where every new leaf has been placed
static int test_insert_set(const char* name, const int* items, const char* const* expected_paths, int count) {
    t_btree* root = bstree_create_node(items[0]);
    int ok = root != NULL;
    printf("%s:\n", name);
    for (int i = 0; i < count && ok; i++) {
        char path[MAX_PATH_LENGTH];
        if (i > 0) {
            bstree_insert(root, items[i], bstree_compare);
        }
        const t_btree* leaf = trace_insertion(root, items[i], path);
        ok = leaf->item == items[i] && leaf->left == NULL && leaf->right == NULL;
        ok = ok && strcmp(path, expected_paths[i]) == 0;
        printf("  insert %d: ", items[i]);
        print_location(root, path);
        printf(" [%s]\n", ok ? "SUCCESS" : "FAIL");
    }
    printf("  result: %s\n", ok ? "SUCCESS" : "FAIL");
    bstree_destroy(root);
    return ok ? SUCCESS : FAIL;
}

// Insertion into an empty tree or without a comparator must do nothing
static int test_invalid_arguments(void) {
    t_btree* root = bstree_create_node(4);
    bstree_insert(NULL, 1, bstree_compare);
    bstree_insert(root, 1, NULL);
    int ok = root != NULL && root->left == NULL && root->right == NULL;
    printf("Insert with NULL root or NULL comparator: %s\n", ok ? "SUCCESS" : "FAIL");
    bstree_destroy(root);
    return ok ? SUCCESS : FAIL;
}

// Follows the insertion rule from the root and writes the steps into path.
// Returns the last node on the way, which is the leaf with the most recently inserted item.
static const t_btree* trace_insertion(const t_btree* root, int item, char* path) {
    const t_btree* last = root;
    const t_btree* next = root;
    int length = 0;
    while (next != NULL && length < MAX_PATH_LENGTH - 1) {
        last = next;
        int go_left = bstree_compare(item, last->item) < 0;
        next = go_left ? last->left : last->right;
        if (next != NULL) {
            path[length] = go_left ? 'L' : 'R';
            length++;
        }
    }
    path[length] = '\0';
    return last;
}

// Prints the path from the root to the node, e.g. "root(4) -> left(2) -> right(3)"
static void print_location(const t_btree* root, const char* path) {
    const t_btree* current = root;
    printf("root(%d)", current->item);
    for (int i = 0; path[i] != '\0'; i++) {
        current = path[i] == 'L' ? current->left : current->right;
        printf(" -> %s(%d)", path[i] == 'L' ? "left" : "right", current->item);
    }
}
