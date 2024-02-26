#ifndef __STRING_WRAP_H__
#define __STRING_WRAP_H__

/** @file

      +----------------------------------------------+
      |        _            _                        |
      |  ___  | |_   _ __  (_)  _ __     __ _   ___  |
      | / __| | __| | '__| | | | '_ \   / _` | / __| |
      | \__ \ | |_  | |    | | | | | | | (_| | \__ \ |
      | |___/  \__| |_|    |_| |_| |_|  \__, | |___/ |
      |                                 |___/        |
      +----------------------------------------------+

 * @brief Wrapper for std string lib
 *
 * <string_*> - works with two string object's
 * <str_*>    - work with string object as dst and C-string as src
 * All func's realloc memory for string's object buffer if current size not enough
 */

#include <stddef.h>

typedef struct {
    char* string;
    size_t length; // for len of current writed string
    size_t size;   // for buffer size
} string;


/**
 * @brief Create string and return pointer
 * @note Just alloc memory for both: object and buffer
 * @warning Abort if can't allocate memory
 * @return ptr to string object */
string* string_create();

/**
 * @brief Create string from C-string and return object
 * @param[in] str - C-string for copy
 * @return ptr to string object */
string* string_create_from(char* str);

/**
 * @brief Destroy string object correctly and return new address
 * @param[in] obj - string object for destroy
 * @return void */
string* string_destroy(string* obj);


/**
 * @brief Write all content from string obj src to string obj dst
 * @note Overwrite lenght attribute
 * @param[out] dst - string object for write in
 * @param[in]  src - string object read from
 * @return count of writed symbol's */
size_t string_write(string* dst, string* src);

/**
 * @brief Write all content from C-string src to string obj dst
 * @note Overwrite lenght attribute
 * @param[out] dst - string object for write in
 * @param[in]  src - C-string read from
 * @return count of writed symbol's */
size_t str_write(string* dst, char* src);


/**
 * @brief Concatinate content from string obj src to string obj dst
 * @note Adding lenght for dst object
 * @param[out] dst - string object for concatinate with
 * @param[in]  src - string object read from
 * @return count of writed symbol's */
size_t string_cat(string* dst, string* src);

/**
 * @brief Concatinate content from C-string src to string obj dst
 * @note Adding lenght for dst object
 * @param[out] dst - string object for concatinate with
 * @param[in]  src - C-string read from
 * @return count of writed symbol's */
size_t str_cat(string* dst, char* src);

/**
 * @brief Clear buffer in given string object
 * @warning Modify input arg
 * @param[in, out] obj - string object for clear
 * @return void */
void string_clear(string* obj);

#endif
