#ifndef __STRING_WRAP_H__
#define __STRING_WRAP_H__

/*
      +----------------------------------------------+
      |        _            _                        |
      |  ___  | |_   _ __  (_)  _ __     __ _   ___  |
      | / __| | __| | '__| | | | '_ \   / _` | / __| |
      | \__ \ | |_  | |    | | | | | | | (_| | \__ \ |
      | |___/  \__| |_|    |_| |_| |_|  \__, | |___/ |
      |                                 |___/        |
      +----------------------------------------------+

 * Wrapper for std string lib
 * <string_*> - works with two string object's
 * <str_*>    - work with string object as dst and C-string as src
 * All func's realloc memory for string's object buffer if not enough current size
 */

#include <stddef.h>

typedef struct {
    char* string;
    size_t length; // for len of current writed string
    size_t size;   // for buffer size
} string;


string* string_create();
/* Create string and return pointer
 * - Just alloc memory for both: object and buffer
 * - Abort if can't allocate memory
 * ret: ptr to string object */

string* string_create_from(char* str);
/* Create string from C-string and return object
 * 1:   str - C-string for copy
 * ret: ptr to string object */

string* string_destroy(string* obj);
/* Destroy string object correctly and return new address
 * 1:   obj - string object ptr for destroy
 * ret: void */


size_t string_write(string* dst, string* src);
/* Write all content from string obj src to string obj dst
 * - Overwrite lenght attribute
 * 1:   dst - string object for write in
 * 2:   src - string object read from
 * ret: count of writed symbol's */

size_t str_write(string* dst, char* src);
/* Write all content from C-string src to string obj dst
 * - Overwrite lenght attribute
 * 1:   dst - string object for write in
 * 2:   src - C-string read from
 * ret: count of writed symbol's */


size_t string_cat(string* dst, string* src);
/* Concatinate content from string obj src to string obj dst
 * - Adding lenght for dst object
 * 1:   dst - string object for concatinate with
 * 2:   src - string object read from
 * ret: count of writed symbol's */

size_t str_cat(string* dst, char* src);
/* Concatinate content from C-string src to string obj dst
 * - Adding lenght for dst object
 * 1:   dst - string object for concatinate with
 * 2:   src - C-string read from
 * ret: count of writed symbol's */


#endif
