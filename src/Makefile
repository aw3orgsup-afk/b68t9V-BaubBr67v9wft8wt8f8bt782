CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
BUILD_DIR = ../build

STAGES = door_struct list_test stack_test print_module documentation_module \
         bst_create_test bst_insert_test bst_traverse_test

.PHONY: all clean rebuild $(STAGES)

all: $(STAGES)

door_struct: | $(BUILD_DIR)
	$(CC) $(CFLAGS) dmanager_module.c -o $(BUILD_DIR)/Quest_1

list_test: | $(BUILD_DIR)
	$(CC) $(CFLAGS) list_test.c list.c -o $(BUILD_DIR)/Quest_2

stack_test: | $(BUILD_DIR)
	$(CC) $(CFLAGS) stack_test.c stack.c -o $(BUILD_DIR)/Quest_3

print_module: | $(BUILD_DIR)
	$(CC) $(CFLAGS) main_module_entry_point.c print_module.c -o $(BUILD_DIR)/Quest_4

documentation_module: | $(BUILD_DIR)
	$(CC) $(CFLAGS) -DDOCUMENTATION_MODULE main_module_entry_point.c print_module.c documentation_module.c \
		-o $(BUILD_DIR)/Quest_5

bst_create_test: | $(BUILD_DIR)
	$(CC) $(CFLAGS) bst_create_test.c bst.c -o $(BUILD_DIR)/Quest_6

bst_insert_test: | $(BUILD_DIR)
	$(CC) $(CFLAGS) bst_insert_test.c bst.c -o $(BUILD_DIR)/Quest_7

bst_traverse_test: | $(BUILD_DIR)
	$(CC) $(CFLAGS) bst_traverse_test.c bst.c -o $(BUILD_DIR)/Quest_8

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all
