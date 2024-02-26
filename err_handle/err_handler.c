/**
 * @file
 * @brief Contains function implementation for 'err_handler' module
 */

#include "err_handler.h"
#include <stdlib.h>

int rough_is_null(void* ptr) {
    if (ptr == NULL) {
        exit(MEMORY_ERROR);
    }

    return NO_ERROR;
}

int soft_is_null(void* ptr) {
    int status = NO_ERROR;

    if (ptr == NULL) {
        status = ERROR;
    }

    return status;
}

