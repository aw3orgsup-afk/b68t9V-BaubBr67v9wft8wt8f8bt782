#ifndef LIST_H
#define LIST_H

#include "door_struct.h"

struct node {
    struct door door;
    struct node* next;
};

// Creates a one-element list with the given door. Returns NULL on allocation failure.
struct node* init(struct door door);

// Inserts a new door right after elem. Returns the new node or NULL on error.
struct node* add_door(struct node* elem, struct door door);

// Returns the first node with the given door id or NULL if there is none.
struct node* find_door(int door_id, struct node* root);

// Removes elem from the list and frees it. Returns the (possibly new) list root.
struct node* remove_door(struct node* elem, struct node* root);

// Frees every node of the list.
void destroy(struct node* root);

#endif  // LIST_H
