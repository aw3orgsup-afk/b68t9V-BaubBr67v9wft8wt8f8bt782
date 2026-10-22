#include "list.h"

#include <stdlib.h>

struct node* init(struct door door) {
    struct node* root = malloc(sizeof(struct node));
    if (root != NULL) {
        root->door = door;
        root->next = NULL;
    }
    return root;
}

struct node* add_door(struct node* elem, struct door door) {
    if (elem == NULL) return NULL;
    struct node* new_node = init(door);
    if (new_node != NULL) {
        new_node->next = elem->next;
        elem->next = new_node;
    }
    return new_node;
}

struct node* find_door(int door_id, struct node* root) {
    struct node* current = root;
    while (current != NULL && current->door.id != door_id) {
        current = current->next;
    }
    return current;
}

struct node* remove_door(struct node* elem, struct node* root) {
    if (elem == NULL || root == NULL) return root;
    struct node* new_root = root;
    if (elem == root) {
        new_root = root->next;
        free(elem);
    } else {
        struct node* prev = root;
        while (prev->next != NULL && prev->next != elem) {
            prev = prev->next;
        }
        if (prev->next == elem) {
            prev->next = elem->next;
            free(elem);
        }
    }
    return new_root;
}

void destroy(struct node* root) {
    while (root != NULL) {
        struct node* next = root->next;
        free(root);
        root = next;
    }
}
