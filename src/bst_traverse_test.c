#include <stdio.h>

#include "bst.h"

#define SUCCESS 0
#define FAIL 1
#define MAX_VISITS 32

struct visit_log {
    int items[MAX_VISITS];
    int count;
};

struct traversal {
    const char* name;
    void (*apply)(t_btree*, void (*)(int));
};

struct traverse_set {
    const char* name;
    const int* items;
    int count;
    const int* infix;
    const int* prefix;
    const int* postfix;
};

static int test_modules_set(void);
static int test_ascending_set(void);
static int test_duplicates_set(void);
static int test_empty_tree(void);
static int test_traverse_set(const struct traverse_set* set);
static int check_traversal(t_btree* root, const struct traversal* traversal, const int* expected, int count);
static t_btree* build_tree(const int* items, int count);
static struct visit_log* get_visit_log(void);
static void print_item(int item);
static void print_and_log_item(int item);

int main(void) {
    int failed = 0;
    failed += test_modules_set() == FAIL;
    failed += test_ascending_set() == FAIL;
    failed += test_duplicates_set() == FAIL;
    failed += test_empty_tree() == FAIL;
    return failed > 0;
}

// The same input sets as in bst_insert_test.c
static int test_modules_set(void) {
    const int items[] = {4, 2, 8, 1, 3, 6, 9, 0, 5, 7, 10};
    const int infix[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int prefix[] = {4, 2, 1, 0, 3, 8, 6, 5, 7, 9, 10};
    const int postfix[] = {0, 1, 3, 2, 5, 7, 6, 10, 9, 8, 4};
    const struct traverse_set set = {
        "Set 1 (modules 0..10, documentation module 4 is the root)", items, 11, infix, prefix, postfix};
    return test_traverse_set(&set);
}

static int test_ascending_set(void) {
    const int items[] = {1, 2, 3, 4, 5};
    const int postfix[] = {5, 4, 3, 2, 1};
    const struct traverse_set set = {
        "Set 2 (ascending values, degenerate tree)", items, 5, items, items, postfix};
    return test_traverse_set(&set);
}

static int test_duplicates_set(void) {
    const int items[] = {0, -5, 5, -5, 0, 3};
    const int infix[] = {-5, -5, 0, 0, 3, 5};
    const int prefix[] = {0, -5, -5, 5, 0, 3};
    const int postfix[] = {-5, -5, 3, 0, 5, 0};
    const struct traverse_set set = {
        "Set 3 (negative and repeated values)", items, 6, infix, prefix, postfix};
    return test_traverse_set(&set);
}

// An empty tree must not call applyf, a NULL applyf must be ignored
static int test_empty_tree(void) {
    const int none[] = {0};
    const struct traverse_set set = {"Set 4 (empty tree)", none, 0, none, none, none};
    t_btree* single = bstree_create_node(1);
    bstree_apply_infix(single, NULL);
    bstree_apply_prefix(single, NULL);
    bstree_apply_postfix(single, NULL);
    bstree_destroy(single);
    return test_traverse_set(&set);
}

// Builds the tree from the set and checks all three traversals of it
static int test_traverse_set(const struct traverse_set* set) {
    const struct traversal infix = {"infix", bstree_apply_infix};
    const struct traversal prefix = {"prefix", bstree_apply_prefix};
    const struct traversal postfix = {"postfix", bstree_apply_postfix};
    t_btree* root = build_tree(set->items, set->count);
    int ok = set->count == 0 || root != NULL;
    printf("%s:\n", set->name);
    ok = check_traversal(root, &infix, set->infix, set->count) == SUCCESS && ok;
    ok = check_traversal(root, &prefix, set->prefix, set->count) == SUCCESS && ok;
    ok = check_traversal(root, &postfix, set->postfix, set->count) == SUCCESS && ok;
    printf("  result: %s\n", ok ? "SUCCESS" : "FAIL");
    bstree_destroy(root);
    return ok ? SUCCESS : FAIL;
}

// Prints the tree with the given traversal and compares the visiting order with the expected one
static int check_traversal(t_btree* root, const struct traversal* traversal, const int* expected, int count) {
    struct visit_log* visits = get_visit_log();
    visits->count = 0;
    printf("  %-8s:", traversal->name);
    traversal->apply(root, print_and_log_item);
    int ok = visits->count == count;
    for (int i = 0; i < count && ok; i++) {
        ok = visits->items[i] == expected[i];
    }
    printf(" [%s]\n", ok ? "SUCCESS" : "FAIL");
    return ok ? SUCCESS : FAIL;
}

// Returns NULL for an empty set or if the root could not be created
static t_btree* build_tree(const int* items, int count) {
    t_btree* root = NULL;
    if (count > 0) {
        root = bstree_create_node(items[0]);
    }
    for (int i = 1; i < count && root != NULL; i++) {
        bstree_insert(root, items[i], bstree_compare);
    }
    return root;
}

// applyf gets nothing but the item, so the visited items are kept here between the calls
static struct visit_log* get_visit_log(void) {
    static struct visit_log visits = {{0}, 0};
    return &visits;
}

// applyf implementation: prints the node value to the terminal
static void print_item(int item) { printf(" %d", item); }

// applyf for checks: prints the node value and remembers it
static void print_and_log_item(int item) {
    struct visit_log* visits = get_visit_log();
    if (visits->count < MAX_VISITS) {
        visits->items[visits->count] = item;
        visits->count++;
    }
    print_item(item);
}
