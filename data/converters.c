/**
 * @file
 * @brief File with data converters
 *
 * Contains functions for convert data for next processing
 */

#include "../formater/types.h"
#include "../views/views.h"
#include <stdio.h>

/* Convert byte to string object as c-byte
 * 1:   symb - byte for convert
 * ret: result - string object ptr */
static string* convert_byte_c_type(uint8_t symb, string* obj);

/* Convert byte to string object as py-byte
 * 1:   symb - byte for convert
 * ret: result - string object ptr */
static string* convert_byte_py_type(uint8_t symb, string* obj);

/* Convert byte to string object as asm-byte
 * 1:   symb - byte for convert
 * ret: result - string object ptr */
static string* convert_byte_asm_type(uint8_t symb, string* obj);

/// @brief typedef for inner functions for store them in array
typedef string* (*convert_byte_func)(uint8_t, string*);

/// @brief struct for alias functions with convert type
typedef struct _convert_byte_table {
    byte_type type;
    convert_byte_func func;
} convert_byte_table;

/// @brief aliased functions with types
const convert_byte_table CONVERT_TABLE[type_end] = {
    {c_type, &convert_byte_c_type},
    {py_type, &convert_byte_py_type},
    {asm_type, &convert_byte_asm_type},
    {0, 0}
};

static string* convert_byte_c_type(uint8_t symb, string* obj) {
    char buffer [15] = {0};
    sprintf(buffer, "%02x", symb);
    str_write(obj, buffer);
    return obj;
}

static string* convert_byte_py_type(uint8_t symb, string* obj) {
    char buffer [15] = {0};
    sprintf(buffer, "\\x%02x", symb);
    str_write(obj, buffer);
    return obj;
}

static string* convert_byte_asm_type(uint8_t symb, string* obj) {
    char buffer [15] = {0};
    sprintf(buffer, "%02xh", symb);
    str_write(obj, buffer);
    return obj;
}

string* convert_byte_to_str(byte_type search, uint8_t byte, string* buffer_out) {
    int index = 0;

    while (CONVERT_TABLE[index].func != 0) {

        if (CONVERT_TABLE[index].type == search) {
            CONVERT_TABLE[index].func(byte, buffer_out);
        }

        index++;
    }

    return buffer_out;
}


