#ifndef DOCUMENTATION_MODULE_H
#define DOCUMENTATION_MODULE_H

#include <stdio.h>
#include <string.h>

#define Documents "Linked lists", "Queues", "Maps", "Binary Trees"
#define Available_document "Binary Trees"
#define Documents_count 4
#define Max_documents_count 16

/*
    input: validation callback, documents count, args with documents names (max 16)
    output: binary mask of documents availability (allocated with malloc, must be freed by the caller)
            or NULL if arguments are invalid or memory allocation failed
*/
int* check_available_documentation_module(int (*validate)(char*), int document_count, ...);

int validate(char* data);

#endif  // DOCUMENTATION_MODULE_H
