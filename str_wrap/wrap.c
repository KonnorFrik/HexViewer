#include "wrap.h"
#include <string.h>
#include <stdlib.h>

static int string_realloc(string* obj);
static size_t calc_new_size(size_t old_size);

static int string_realloc(string* obj) {
    /* Make realloc for string object
     * 1:   obj - string object for realloc his buffer
     * ret: realloc_status - 0 = No realloc, 1 = Good realloc*/

    size_t new_size = calc_new_size(obj->size);
    char* tmp = realloc(obj->string, new_size);
    int realloc_status = 0;

    if (tmp) {
        obj->string = tmp;
        obj->size = new_size;
        realloc_status = 1;
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

size_t string_write(string* dst, string* src) {
    /* Write all content from string obj src to string obj dst
     * - Overwrite lenght attribute
     * 1:   dst - string object for write in
     * 2:   src - string object read from
     * ret: count of writed symbol's */

    //check result size and realloc if needed
    if (src->len >= dst->size) {
        if (!string_realloc(dst)) {
            // handle error 
        }
    }

    //copy symbol's from src to dst
    //for (size_t ind = 0; ind < src->len; ++ind, ++count) {
        //dst->string[ind] = src->string[ind];
    //}
    size_t count = src->len + 1; // +1 -> include '\0' for copy
    strncpy(dst->string, src->string, count);
    dst->len = count - 1; //only length of str, without '\0'

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
        if (!string_realloc(dst)) {
            // handle error 
        }
    }

    strncpy(dst->string, src, count);
    dst->len = count - 1; //only length of str, without '\0'

    return count;
}

size_t string_cat(string* dst, string* src) {
    /* Concatinate content from string obj src to string obj dst
     * - Adding lenght for dst object
     * 1:   dst - string object for concatinate with
     * 2:   src - string object read from
     * ret: count of writed symbol's */

    //check result size and realloc if needed
    if ((dst->size + src->len) >= dst->size) {
        if (!string_realloc(dst)) {
            // handle error 
        }
    }

    size_t count = src->len + 1;
    strncpy(dst->string + dst->len, src->string, count); 
    dst->len += count - 1;

    return count;
}

size_t str_cat(string* dst, char* src) {
    /* Concatinate content from C-string src to string obj dst
     * - Adding lenght for dst object
     * 1:   dst - string object for concatinate with
     * 2:   src - C-string read from
     * ret: count of writed symbol's */

    size_t count = strlen(src) + 1;

    if ((dst->len + count) >= dst->size) {
        if (!string_realloc(dst)) {
            // handle error 
        }
    }

    strncpy(dst->string + dst->len, src, count);
    dst->len += count - 1;

    return count;
}
