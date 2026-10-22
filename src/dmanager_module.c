#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

static void initialize_doors(struct door* doors);
static void sort_doors_by_id(struct door* doors, int count);
static void close_doors(struct door* doors, int count);
static void print_doors(const struct door* doors, int count);

int main() {
    struct door doors[DOORS_COUNT];

    initialize_doors(doors);
    sort_doors_by_id(doors, DOORS_COUNT);
    close_doors(doors, DOORS_COUNT);
    print_doors(doors, DOORS_COUNT);

    return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door* doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

// Insertion sort in ascending order of door id
static void sort_doors_by_id(struct door* doors, int count) {
    for (int i = 1; i < count; i++) {
        struct door current = doors[i];
        int j = i - 1;
        while (j >= 0 && doors[j].id > current.id) {
            doors[j + 1] = doors[j];
            j--;
        }
        doors[j + 1] = current;
    }
}

static void close_doors(struct door* doors, int count) {
    for (int i = 0; i < count; i++) {
        doors[i].status = DOOR_CLOSED;
    }
}

// Prints "id, status" lines without a trailing newline
static void print_doors(const struct door* doors, int count) {
    for (int i = 0; i < count; i++) {
        if (i > 0) {
            printf("\n");
        }
        printf("%d, %d", doors[i].id, doors[i].status);
    }
}
