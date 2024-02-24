/**
 * \file
 * \brief File with data printers
 */
#include "views.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static void apply_byte_format(string* byte_str, page_format* format);
/* Apply output rules from page_format obj for converted str
 * 1:   byte_str - string object ptr for modify
 * 2:   format - page_format object ptr with rules
 * ret: void */

static void apply_byte_format(string* byte_str, page_format* format) {
    if (format->byte_format.is_upper) {
        size_t ind = 0;

        while (ind < byte_str->length) {
            if (islower(byte_str->string[ind])) {
                byte_str->string[ind] ^= 32;
            }

            ind++;
        }
    }
}

void print_address(uint64_t address, page_format* format) {
    char fmt[37] = {0};

    if (format->row_format.address_len < 30 &&
        format->row_format.address_len > 0) {
        sprintf(fmt, "%%0%dl", format->row_format.address_len);

    } else {
        sprintf(fmt, "%%04l");
    }

    size_t current_fmt_len = strlen(fmt);

    switch (format->row_format.address_type) {
        case hex_type:
            sprintf(fmt + current_fmt_len, "x");
            break;

        case dec_type:
            sprintf(fmt + current_fmt_len, "u");
            break;

        case oct_type:
            sprintf(fmt + current_fmt_len, "o");
            break;
    }

    printf(fmt, address); 
}

void print_byte_row(page_format* format) {
    string* byte_str = string_create();
    for (uint8_t count = 0; count < format->row_format.bytes_len; ++count) {
        //string* byte_str = convert_byte_to_str(format->byte_format.type, format->current_row[count]);
        convert_byte_to_str(format->byte_format.type, format->current_row[count], byte_str);

        apply_byte_format(byte_str, format);

        printf("%s%c",
                byte_str->string,
                format->row_format.bytes_delimiter);

        string_clear(byte_str);
    }

    string_destroy(byte_str);
}

void decode_print_row(page_format* format) {
    for (uint8_t count = 0; count < format->row_format.bytes_len; ++count) {
        char symb = decode_symb(format->current_row[count], format);

        printf("%c", symb);
    }
}


