#ifndef STACK_H
#define STACK_H

#define STACK_OK 0
#define STACK_ERROR 1

struct stack_node {
    int value;
    struct stack_node* next;
};

struct stack {
    struct stack_node* top;
    int size;
};

// Creates an empty stack. Returns NULL on allocation failure.
struct stack* init(void);

// Puts value on top of the stack. Returns STACK_OK or STACK_ERROR.
int push(struct stack* stack, int value);

// Takes the top value off the stack and writes it to value.
// Returns STACK_ERROR if the stack is empty or arguments are NULL.
int pop(struct stack* stack, int* value);

// Frees the stack with all its elements.
void destroy(struct stack* stack);

#endif  // STACK_H
