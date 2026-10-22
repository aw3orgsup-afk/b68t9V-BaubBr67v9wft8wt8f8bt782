#include "documentation_module.h"

#include <stdarg.h>
#include <stdlib.h>

int validate(char* data) {
    int validation_result = data != NULL && !strcmp(data, Available_document);
    return validation_result;
}

int* check_available_documentation_module(int (*validate)(char*), int document_count, ...) {
    if (validate == NULL || document_count <= 0 || document_count > Max_documents_count) return NULL;
    int* availability_mask = malloc(document_count * sizeof(int));
    if (availability_mask != NULL) {
        va_list documents;
        va_start(documents, document_count);
        for (int i = 0; i < document_count; i++) {
            availability_mask[i] = validate(va_arg(documents, char*)) ? 1 : 0;
        }
        va_end(documents);
    }
    return availability_mask;
}
