#include "err_handler.h"
#include <stdlib.h>

int rough_is_null(void* ptr) {
    /* Immediately abort all programm if Null given, return 0 otheriwse
     * 1:   ptr - memory pointer for check
     * ret: void */

    if (ptr == 0) {
        exit(MEMORY_ERROR);
    }

    return 0;
}

int soft_is_null(void* ptr) {
    /* Return 1 if Null given, 0 otherwise
     * 1:   ptr - memory pointer for check
     * ret: void */

    int result = 0;

    if (ptr == 0) {
        result = 1;
    }

    return result;
}

