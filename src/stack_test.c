#include "stack.h"

#include <limits.h>
#include <stdio.h>

#define SUCCESS 0
#define FAIL 1

struct test_case {
    const char* name;
    int (*run)(void);
};

static int test_push_to_empty(void);
static int test_push_many(void);
static int test_push_extreme_values(void);
static int test_push_null_stack(void);
static int test_pop_lifo_order(void);
static int test_pop_empty(void);
static int test_pop_null_args(void);
static int test_push_after_pop(void);

int main(void) {
    const struct test_case tests[] = {
        {"push to an empty stack", test_push_to_empty},
        {"push many values", test_push_many},
        {"push INT_MIN and INT_MAX", test_push_extreme_values},
        {"push to a NULL stack", test_push_null_stack},
        {"pop in LIFO order", test_pop_lifo_order},
        {"pop from an empty stack", test_pop_empty},
        {"pop with NULL arguments", test_pop_null_args},
        {"push after pop", test_push_after_pop},
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

static int test_push_to_empty(void) {
    struct stack* stack = init();
    int ok = stack != NULL && stack->size == 0 && stack->top == NULL;
    ok = ok && push(stack, 42) == STACK_OK;
    ok = ok && stack->size == 1 && stack->top->value == 42 && stack->top->next == NULL;
    destroy(stack);
    return ok ? SUCCESS : FAIL;
}

static int test_push_many(void) {
    struct stack* stack = init();
    int ok = stack != NULL;
    for (int i = 1; i <= 100 && ok; i++) {
        ok = push(stack, i) == STACK_OK && stack->size == i && stack->top->value == i;
    }
    destroy(stack);
    return ok ? SUCCESS : FAIL;
}

static int test_push_extreme_values(void) {
    struct stack* stack = init();
    int top = 0;
    int ok = stack != NULL && push(stack, INT_MIN) == STACK_OK && push(stack, INT_MAX) == STACK_OK;
    ok = ok && pop(stack, &top) == STACK_OK && top == INT_MAX;
    ok = ok && pop(stack, &top) == STACK_OK && top == INT_MIN;
    destroy(stack);
    return ok ? SUCCESS : FAIL;
}

static int test_push_null_stack(void) { return push(NULL, 1) == STACK_ERROR ? SUCCESS : FAIL; }

static int test_pop_lifo_order(void) {
    const int values[] = {3, -7, 0, 15};
    int count = sizeof(values) / sizeof(values[0]);
    struct stack* stack = init();
    int ok = stack != NULL;
    for (int i = 0; i < count && ok; i++) {
        ok = push(stack, values[i]) == STACK_OK;
    }
    for (int i = count - 1; i >= 0 && ok; i--) {
        int value = 0;
        ok = pop(stack, &value) == STACK_OK && value == values[i] && stack->size == i;
    }
    ok = ok && stack->top == NULL;
    destroy(stack);
    return ok ? SUCCESS : FAIL;
}

// Popping from an empty stack must fail and keep the output variable untouched
static int test_pop_empty(void) {
    struct stack* stack = init();
    int value = 123;
    int ok = stack != NULL && pop(stack, &value) == STACK_ERROR && value == 123 && stack->size == 0;
    destroy(stack);
    return ok ? SUCCESS : FAIL;
}

static int test_pop_null_args(void) {
    struct stack* stack = init();
    int value = 0;
    int ok = stack != NULL && push(stack, 5) == STACK_OK;
    ok = ok && pop(stack, NULL) == STACK_ERROR && stack->size == 1;
    ok = ok && pop(NULL, &value) == STACK_ERROR;
    destroy(stack);
    return ok ? SUCCESS : FAIL;
}

static int test_push_after_pop(void) {
    struct stack* stack = init();
    int value = 0;
    int ok = stack != NULL && push(stack, 1) == STACK_OK && pop(stack, &value) == STACK_OK;
    ok = ok && push(stack, 2) == STACK_OK && stack->size == 1;
    ok = ok && pop(stack, &value) == STACK_OK && value == 2 && pop(stack, &value) == STACK_ERROR;
    destroy(stack);
    return ok ? SUCCESS : FAIL;
}
