#include <limits.h>
#include <stdio.h>

#include "bst.h"

#define SUCCESS 0
#define FAIL 1

static int test_create_node(int item);

int main(void) {
    // 4 is the documentation module id, 0 and 10 are the bounds of module ids
    const int items[] = {4, 0, 10, -7, INT_MIN, INT_MAX};
    int count = sizeof(items) / sizeof(items[0]);
    int failed = 0;
    for (int i = 0; i < count; i++) {
        failed += test_create_node(items[i]) == FAIL;
    }
    return failed > 0;
}

// Creates a node and checks that it stores the value and has no children
static int test_create_node(int item) {
    t_btree* node = bstree_create_node(item);
    int ok = node != NULL && node->item == item && node->left == NULL && node->right == NULL;
    printf("bstree_create_node(%d): ", item);
    if (node != NULL) {
        printf("item = %d, left = %s, right = %s", node->item, node->left == NULL ? "NULL" : "not NULL",
               node->right == NULL ? "NULL" : "not NULL");
    } else {
        printf("node was not created");
    }
    printf(" [%s]\n", ok ? "SUCCESS" : "FAIL");
    bstree_destroy(node);
    return ok ? SUCCESS : FAIL;
}
