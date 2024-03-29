/** @file
 * @brief implementation of string wrap module
 */

#include "wrap.h"
#include "../err_handle/err_handler.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>


static void safe_string_realloc(string* obj, size_t new_size);
static error_code string_realloc(string* obj, size_t new_size);

/* Make realloc for string object to given size and return status
 * 1:   obj - string object for realloc his buffer
 * ret: realloc_status - NO_ERROR or REALLOC_ERROR*/
static error_code string_realloc(string* obj, size_t new_size) {

    char* tmp = realloc(obj->string, new_size);
    error_code realloc_status = REALLOC_ERROR;

    if (tmp) {
        obj->string = tmp;
        obj->size = new_size;
        realloc_status = NO_ERROR;
    }

    return realloc_status;
}

/* Check status code from 'string_realloc' and handles it
 * - Abort for any error 
 * 1:   obj - string object for realloc his buffer
 * ret: void */
static void safe_string_realloc(string* obj, size_t new_size) {

    if (obj->size == new_size) {
        return;
    }

    if (string_realloc(obj, new_size) != NO_ERROR) {
        // handle error 
        exit(REALLOC_ERROR);
    }
}

string* string_create() {
    string* obj = calloc(1, sizeof(string));
    obj->length = 0;

    if (!soft_is_null(obj)) {
        obj->size = 1;
        obj->string = calloc(obj->size, sizeof(char));
    }

    rough_is_null(obj);
    rough_is_null(obj->string);

    return obj;
}

string* string_create_from(char* str) {
    string* obj = string_create();

    if (!soft_is_null(str)) {
        str_write(obj, str);
    }

    return obj;
}

string* string_destroy(string* obj) {
    string* ret = obj;

    if (!soft_is_null(obj)) {
        if (!soft_is_null(obj->string)) {
            free(obj->string);
        }

        free(obj);
        ret = 0;
    }

    return ret;
}

size_t string_write(string* dst, string* src) {
    size_t count = 0;

    if (soft_is_null(dst) ||
        soft_is_null(src) ||
        soft_is_null(dst->string) ||
        soft_is_null(src->string)) {

        return count;
    }

    //check result size and realloc if needed
    if (src->length >= dst->size) {
        safe_string_realloc(dst, src->length + 1);
    }

    count = src->length + 1; // +1 -> include '\0' for copy
    strncpy(dst->string, src->string, count);
    dst->length = count - 1; //only length of str, without '\0'

    return count;
}

size_t str_write(string* dst, char* src) {
    size_t count = 0;

    if (soft_is_null(dst) ||
        soft_is_null(dst->string) ||
        soft_is_null(src)) {

        return count;
    }

    count = strlen(src) + 1;

    if (count >= dst->size) {
        safe_string_realloc(dst, count);
    }

    strncpy(dst->string, src, count);
    dst->length = count - 1; //only length of str, without '\0'

    return count;
}

size_t string_cat(string* dst, string* src) {
    size_t count = 0;

    if (soft_is_null(dst) ||
        soft_is_null(src) ||
        soft_is_null(dst->string) ||
        soft_is_null(src->string)) {

        return count;
    }

    count = src->length + 1;

    if (count == 1) {
        count = 0;
    }

    //check result size and realloc if needed
    if ((dst->size + src->length) >= dst->size) {
        safe_string_realloc(dst, src->length + dst->size);
    }

    if (count) {
        strncpy(dst->string + dst->length, src->string, count); 
        dst->length += count - 1;
    }

    return count;
}

size_t str_cat(string* dst, char* src) {
    size_t count = 0;

    if (soft_is_null(dst) ||
        soft_is_null(dst->string) ||
        soft_is_null(src)) {

        return count;
    }
    
    count = strlen(src) + 1;

    if (count == 1) {
        count = 0;
    }

    if ((dst->length + count) >= dst->size) {
        safe_string_realloc(dst, dst->length + count);
    }

    if (count) {
        strncpy(dst->string + dst->length, src, count);
        dst->length += count - 1;
    }

    return count;
}

void string_clear(string* obj) {
    if (obj != 0) {
        memset(obj->string, 0, obj->size);
    }
}

size_t str_to_upper(char* str) {
    size_t count = 0;

    if (str == NULL) {
        return count;
    }

    int index = 0;

    while (str[index] != 0) {
        if (islower(str[index])) {
            str[index] ^= 32;
            count++;
        }

        index++;
    }

    return count;
}

size_t str_to_lower(char* str) {
    size_t count = 0;

    if (str == NULL) {
        return count;
    }

    int index = 0;

    while (str[index] != 0) {
        if (isupper(str[index])) {
            str[index] ^= 32;
            count++;
        }
        
        index++;
    }

    return count;
}

size_t string_to_lower(string* str) {
    if (str == NULL) {
        return 0;
    }

    return str_to_lower(str->string);
}

size_t string_to_upper(string* str) {
    if (str == NULL) {
        return 0;
    }

    return str_to_upper(str->string);
}

