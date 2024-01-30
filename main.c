#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str_wrap/wrap.h"
#include "err_handle/err_handler.h"

void string_full_destroy(string** obj) {
    /* Destroy string object correctly and return new address
     * 1:   obj - string object ptr for destroy
     * ret: void */

    if (soft_is_null(obj)) {
        return;
    }

    if (!soft_is_null(*obj)) {
        if (!soft_is_null((*obj)->string)) {
            free((*obj)->string);
            (*obj)->string = 0;
            (*obj)->size = 0;
            (*obj)->length = 0;
        }

        free(*obj);
    }
}

void print_string(string* obj) {
    printf("@string: %p\n", obj);
    printf("\t|->string %p -> '%s'\n", obj->string, obj->string);
    printf("\t|->length %lu\n", obj->length);
    printf("\t|->size %lu\n", obj->size);
    printf("\n");
}

int main() {
    string* obj = string_create();
    print_string(obj);

    string* obj2 = string_create();
    print_string(obj2);

    string* new_ptr = string_destroy(obj);
    print_string(obj);

    string_full_destroy(&obj2);
    print_string(obj2);

    return 0;
}
