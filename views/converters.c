#include "views.h"
//#include <string.h>
#include <stdio.h>

static string* convert_byte_c_type(uint8_t symb);
/* Convert byte to string object as c-byte
 * 1:   symb - byte for convert
 * ret: result - string object ptr */

static string* convert_byte_py_type(uint8_t symb);
/* Convert byte to string object as py-byte
 * 1:   symb - byte for convert
 * ret: result - string object ptr */

typedef string* (*convert_byte_func)(uint8_t);

typedef struct _convert_byte_table {
    byte_type type;
    convert_byte_func func;
} convert_byte_table;

const convert_byte_table CONVERT_TABLE[type_end] = {
    {c_type, &convert_byte_c_type},
    {py_type, &convert_byte_py_type},
    {0, 0}
};

static string* convert_byte_c_type(uint8_t symb) {
    string* obj = string_create();
    char buffer [15] = {0};
    sprintf(buffer, "%02x", symb);
    str_write(obj, buffer);
    return obj;
}

static string* convert_byte_py_type(uint8_t symb) {
    string* obj = string_create();
    char buffer [15] = {0};
    sprintf(buffer, "\\x%02x", symb);
    str_write(obj, buffer);
    return obj;
}

string* convert_byte_to_str(byte_type search, uint8_t byte) {
    string* result = 0;
    int index = 0;

    while (CONVERT_TABLE[index].func != 0) {

        if (CONVERT_TABLE[index].type == search) {
            result = CONVERT_TABLE[index].func(byte);
        }

        index++;
    }

    return result;
}

