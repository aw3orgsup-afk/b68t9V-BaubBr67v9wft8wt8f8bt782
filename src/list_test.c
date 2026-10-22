#include "list.h"

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAIL 1

struct test_case {
    const char* name;
    int (*run)(void);
};

static struct door make_door(int id);
static struct node* build_list(const int* ids, int count);
static struct node* nth_node(struct node* root, int index);
static int list_matches(const struct node* root, const int* ids, int count);

static int test_add_door_after_single(void);
static int test_add_door_in_middle(void);
static int test_add_door_after_tail(void);
static int test_add_door_null_elem(void);
static int test_remove_door_middle(void);
static int test_remove_door_head(void);
static int test_remove_door_tail(void);
static int test_remove_door_last_one(void);
static int test_remove_door_absent(void);
static int test_find_door(void);

int main(void) {
    const struct test_case tests[] = {
        {"add_door after the only node", test_add_door_after_single},
        {"add_door in the middle", test_add_door_in_middle},
        {"add_door after the tail", test_add_door_after_tail},
        {"add_door with NULL elem", test_add_door_null_elem},
        {"remove_door from the middle", test_remove_door_middle},
        {"remove_door of the head", test_remove_door_head},
        {"remove_door of the tail", test_remove_door_tail},
        {"remove_door of the last node", test_remove_door_last_one},
        {"remove_door of a foreign node", test_remove_door_absent},
        {"find_door", test_find_door},
    };
    int count = sizeof(tests) / sizeof(tests[0]);
    int failed = 0;
    for (int i = 0; i < count; i++) {
        int result = tests[i].run();
        printf("%s: %s\n", tests[i].name, result == SUCCESS ? "SUCCESS" : "FAIL");
        failed += result == FAIL;
    }
    return failed > 0;
}

static struct door make_door(int id) {
    struct door door = {id, DOOR_CLOSED};
    return door;
}

// Builds a list with doors in the given order. Returns NULL on failure.
static struct node* build_list(const int* ids, int count) {
    struct node* root = init(make_door(ids[0]));
    struct node* tail = root;
    for (int i = 1; i < count && tail != NULL; i++) {
        tail = add_door(tail, make_door(ids[i]));
    }
    if (tail == NULL) {
        destroy(root);
        root = NULL;
    }
    return root;
}

// Returns the node at the given position or NULL if the list is shorter
static struct node* nth_node(struct node* root, int index) {
    struct node* current = root;
    for (int i = 0; i < index && current != NULL; i++) {
        current = current->next;
    }
    return current;
}

// Checks that the list holds exactly the given door ids in the given order
static int list_matches(const struct node* root, const int* ids, int count) {
    int matches = 1;
    int i = 0;
    const struct node* current = root;
    while (current != NULL && matches) {
        matches = i < count && current->door.id == ids[i];
        current = current->next;
        i++;
    }
    return matches && i == count;
}

static int test_add_door_after_single(void) {
    const int expected[] = {0, 1};
    struct node* root = init(make_door(0));
    struct node* added = add_door(root, make_door(1));
    int ok = added != NULL && root->next == added && added->next == NULL;
    ok = ok && added->door.status == DOOR_CLOSED && list_matches(root, expected, 2);
    destroy(root);
    return ok ? SUCCESS : FAIL;
}

static int test_add_door_in_middle(void) {
    const int ids[] = {0, 1, 2};
    const int expected[] = {0, 1, 7, 2};
    struct node* root = build_list(ids, 3);
    struct node* added = add_door(nth_node(root, 1), make_door(7));
    int ok = added != NULL && added->door.id == 7 && list_matches(root, expected, 4);
    destroy(root);
    return ok ? SUCCESS : FAIL;
}

static int test_add_door_after_tail(void) {
    const int ids[] = {0, 1, 2};
    const int expected[] = {0, 1, 2, 3};
    struct node* root = build_list(ids, 3);
    const struct node* added = add_door(nth_node(root, 2), make_door(3));
    int ok = added != NULL && added->next == NULL && list_matches(root, expected, 4);
    destroy(root);
    return ok ? SUCCESS : FAIL;
}

static int test_add_door_null_elem(void) {
    struct node* added = add_door(NULL, make_door(5));
    int ok = added == NULL;
    destroy(added);
    return ok ? SUCCESS : FAIL;
}

static int test_remove_door_middle(void) {
    const int ids[] = {0, 1, 2, 3, 4};
    const int expected[] = {0, 1, 3, 4};
    struct node* root = build_list(ids, 5);
    struct node* new_root = remove_door(find_door(2, root), root);
    int ok = new_root == root && list_matches(new_root, expected, 4);
    destroy(new_root);
    return ok ? SUCCESS : FAIL;
}

static int test_remove_door_head(void) {
    const int ids[] = {0, 1, 2};
    const int expected[] = {1, 2};
    struct node* root = build_list(ids, 3);
    struct node* second = nth_node(root, 1);
    struct node* new_root = remove_door(root, root);
    int ok = root != NULL && new_root == second && list_matches(new_root, expected, 2);
    destroy(new_root);
    return ok ? SUCCESS : FAIL;
}

static int test_remove_door_tail(void) {
    const int ids[] = {0, 1, 2};
    const int expected[] = {0, 1};
    struct node* root = build_list(ids, 3);
    struct node* new_root = remove_door(find_door(2, root), root);
    int ok = new_root == root && list_matches(new_root, expected, 2);
    destroy(new_root);
    return ok ? SUCCESS : FAIL;
}

static int test_remove_door_last_one(void) {
    struct node* root = init(make_door(9));
    struct node* new_root = remove_door(root, root);
    int ok = new_root == NULL;
    destroy(new_root);
    return ok ? SUCCESS : FAIL;
}

// Removing a node that is not in the list (or NULL) must leave the list untouched
static int test_remove_door_absent(void) {
    const int ids[] = {0, 1, 2};
    struct node* root = build_list(ids, 3);
    struct node* foreign = init(make_door(1));
    struct node* new_root = remove_door(foreign, root);
    int ok = new_root == root && list_matches(new_root, ids, 3);
    new_root = remove_door(NULL, new_root);
    ok = ok && new_root == root && list_matches(new_root, ids, 3);
    ok = ok && remove_door(foreign, NULL) == NULL;
    destroy(foreign);
    destroy(new_root);
    return ok ? SUCCESS : FAIL;
}

static int test_find_door(void) {
    const int ids[] = {4, 8, 15};
    struct node* root = build_list(ids, 3);
    const struct node* found = find_door(8, root);
    int ok = root != NULL && found == nth_node(root, 1);
    ok = ok && find_door(16, root) == NULL && find_door(4, NULL) == NULL;
    destroy(root);
    return ok ? SUCCESS : FAIL;
}
