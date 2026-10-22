#include <stdio.h>
#include <stdlib.h>

#include "print_module.h"

// The documentation part is built only for Quest 5 (see the documentation_module stage in Makefile)
#ifdef DOCUMENTATION_MODULE
#include "documentation_module.h"

static void print_documents_availability(void);
#endif

int main() {
    print_log(print_char, Module_load_success_message);
#ifdef DOCUMENTATION_MODULE
    print_documents_availability();
#endif
    return 0;
}

#ifdef DOCUMENTATION_MODULE
// Prints "document name : (un)available" lines without a trailing newline
static void print_documents_availability(void) {
    int* availability_mask = check_available_documentation_module(validate, Documents_count, Documents);
    if (availability_mask != NULL) {
        const char* documents[] = {Documents};
        for (int i = 0; i < Documents_count; i++) {
            if (i > 0) {
                printf("\n");
            }
            printf("%-15s: %s", documents[i], availability_mask[i] ? "available" : "unavailable");
        }
        free(availability_mask);
    } else {
        printf("n/a");
    }
}
#endif
