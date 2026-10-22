#include "stack.h"

#include <stdlib.h>

struct stack* init(void) {
    struct stack* stack = malloc(sizeof(struct stack));
    if (stack != NULL) {
        stack->top = NULL;
        stack->size = 0;
    }
    return stack;
}

int push(struct stack* stack, int value) {
    if (stack == NULL) return STACK_ERROR;
    int status = STACK_ERROR;
    struct stack_node* new_node = malloc(sizeof(struct stack_node));
    if (new_node != NULL) {
        new_node->value = value;
        new_node->next = stack->top;
        stack->top = new_node;
        stack->size++;
        status = STACK_OK;
    }
    return status;
}

int pop(struct stack* stack, int* value) {
    if (stack == NULL || value == NULL) return STACK_ERROR;
    int status = STACK_ERROR;
    struct stack_node* top = stack->top;
    if (top != NULL) {
        *value = top->value;
        stack->top = top->next;
        stack->size--;
        free(top);
        status = STACK_OK;
    }
    return status;
}

void destroy(struct stack* stack) {
    if (stack != NULL) {
        struct stack_node* current = stack->top;
        while (current != NULL) {
            struct stack_node* next = current->next;
            free(current);
            current = next;
        }
        free(stack);
    }
}
