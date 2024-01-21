#include "wrap.h"
#include "../err_handle/err_handler.h"

#include <string.h>
#include <stdlib.h>


static void safe_string_realloc(string* obj, size_t new_size);
static error_code string_realloc(string* obj, size_t new_size);

static error_code string_realloc(string* obj, size_t new_size) {
    /* Make realloc for string object to given size and return status
     * 1:   obj - string object for realloc his buffer
     * ret: realloc_status - NO_ERROR or REALLOC_ERROR*/

    char* tmp = realloc(obj->string, new_size);
    error_code realloc_status = REALLOC_ERROR;

    if (tmp) {
        obj->string = tmp;
        obj->size = new_size;
        realloc_status = NO_ERROR;
    }

    return realloc_status;
}

static void safe_string_realloc(string* obj, size_t new_size) {
    /* Check status code from 'string_realloc' and handles it
     * - Abort for any error 
     * 1:   obj - string object for realloc his buffer
     * ret: void */

    if (obj->size == new_size) {
        return;
    }

    if (string_realloc(obj, new_size) != NO_ERROR) {
        // handle error 
        exit(status);
    }
}

string* string_create() {
    /* Create string and return pointer
     * - Just alloc memory for both: object and buffer
     * - Abort if can't allocate memory
     * ret: ptr to string object */

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
    /* Create string from C-string and return object
     * 1:   str - C-string for copy
     * ret: ptr to string object */

    string* obj = string_create();

    if (!soft_is_null(str)) {
        str_write(obj, str);
    }

    return obj;
}

string* string_destroy(string* obj) {
    /* Destroy string object correctly and return new address
     * 1:   obj - string object ptr for destroy
     * ret: void */

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
    /* Write all content from string obj src to string obj dst
     * - Overwrite lenght attribute
     * 1:   dst - string object for write in
     * 2:   src - string object read from
     * ret: count of writed symbol's */

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
//TODO add handling of null in both ^ and v
size_t str_write(string* dst, char* src) {
    /* Write all content from C-string src to string obj dst
     * - Overwrite lenght attribute
     * 1:   dst - string object for write in
     * 2:   src - C-string read from
     * ret: count of writed symbol's */

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
    /* Concatinate content from string obj src to string obj dst
     * - Adding lenght for dst object
     * 1:   dst - string object for concatinate with
     * 2:   src - string object read from
     * ret: count of writed symbol's */

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
    /* Concatinate content from C-string src to string obj dst
     * - Adding lenght for dst object
     * 1:   dst - string object for concatinate with
     * 2:   src - C-string read from
     * ret: count of writed symbol's */

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
