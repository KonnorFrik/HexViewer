#include "wrap.h"
#include "../err_handle/err_handler.h"

#include <string.h>
#include <stdlib.h>


static void safe_string_realloc(string* obj);
static error_code string_realloc(string* obj);
static size_t calc_new_size(size_t old_size);

static error_code string_realloc(string* obj) {
    /* Make realloc for string object
     * 1:   obj - string object for realloc his buffer
     * ret: realloc_status - 0 = No realloc, 1 = Good realloc*/

    size_t new_size = calc_new_size(obj->size);
    char* tmp = realloc(obj->string, new_size);
    error_code realloc_status = NO_ERROR;

    if (tmp) {
        obj->string = tmp;
        obj->size = new_size;
        realloc_status = REALLOC_ERROR;
    }

    return realloc_status;
}

static size_t calc_new_size(size_t old_size) {
    /* Calculated new size with std-increase formula
     * 1:   old_size - old buffer size for increase
     * ret: new_size - new calculated size */

    size_t new_len = 0;
    new_len = old_size + (old_size / 2);

    if (old_size == 1) {
        new_len++;
    }
    
    return new_len;
}

static void safe_string_realloc(string* obj) {
    /* Check status code from 'string_realloc' and handle it
     * - Abort for any error 
     * 1:   obj - string object for realloc his buffer
     * ret: void */

    error_code status = NO_ERROR;

    if ((status = string_realloc(obj)) != NO_ERROR) {
        // handle error 
        exit(status);
    }
}

string* string_create() {
    /* Create string and return pointer
     * - Just alloc memory for both: object and buffer
     * - Abort if can't alloc memory
     * ret: ptr to string object */

    string* obj = calloc(1, sizeof(string));

    if (obj != 0) {
        obj->string = calloc(1, sizeof(char));
        obj->size = 1;
    }

    if (obj == 0 || obj->string == 0) {
        exit(ALLOC_ERROR);
    }

    return obj;
}

string* string_create_from(char* str) {
    /* Create string from C-string and return pointer
     * 1:   str - C-string for copy
     * ret: ptr to string object */

    string* obj = string_create();
    str_write(obj, str);

    return obj;
}

void string_destroy(string* obj) {
    /* Destroy string object correctly
     * 1:   obj - string object ptr for destroy
     * ret: void */

    if (obj != 0) {
        if (obj->string != 0) {
            free(obj->string);
            obj->string = 0;
            obj->size = 0;
            obj->length = 0;
        }

        free(obj);
    }
}

size_t string_write(string* dst, string* src) {
    /* Write all content from string obj src to string obj dst
     * - Overwrite lenght attribute
     * 1:   dst - string object for write in
     * 2:   src - string object read from
     * ret: count of writed symbol's */

    //check result size and realloc if needed
    if (src->length >= dst->size) {
        safe_string_realloc(dst);
    }

    //copy symbol's from src to dst
    //for (size_t ind = 0; ind < src->length; ++ind, ++count) {
        //dst->string[ind] = src->string[ind];
    //}
    size_t count = src->length + 1; // +1 -> include '\0' for copy
    strncpy(dst->string, src->string, count);
    dst->length = count - 1; //only length of str, without '\0'

    return count;
}

size_t str_write(string* dst, char* src) {
    /* Write all content from C-string src to string obj dst
     * - Overwrite lenght attribute
     * 1:   dst - string object for write in
     * 2:   src - C-string read from
     * ret: count of writed symbol's */

    size_t count = strlen(src) + 1; // +1 -> include '\0' for copy

    if (count >= dst->size) {
        safe_string_realloc(dst);
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

    //check result size and realloc if needed
    if ((dst->size + src->length) >= dst->size) {
        safe_string_realloc(dst);
    }

    size_t count = src->length + 1;
    strncpy(dst->string + dst->length, src->string, count); 
    dst->length += count - 1;

    return count;
}

size_t str_cat(string* dst, char* src) {
    /* Concatinate content from C-string src to string obj dst
     * - Adding lenght for dst object
     * 1:   dst - string object for concatinate with
     * 2:   src - C-string read from
     * ret: count of writed symbol's */

    size_t count = strlen(src) + 1;

    if ((dst->length + count) >= dst->size) {
        safe_string_realloc(dst);
    }

    strncpy(dst->string + dst->length, src, count);
    dst->length += count - 1;

    return count;
}
