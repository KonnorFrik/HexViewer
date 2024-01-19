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

//TODO write test's
//and gcovr

typedef struct {
    char* string;
    size_t length; // for len of current writed string
    size_t size;   // for buffer size
} string;

size_t string_write(string* dst, string* src);
size_t str_write(string* dst, char* src);

size_t string_cat(string* dst, string* src);
size_t str_cat(string* dst, char* src);

#endif
