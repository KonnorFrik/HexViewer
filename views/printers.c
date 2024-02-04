#include "views.h"
#include <stdio.h>
//#include <string.h>

void print_address(uint64_t address, page_format* format) {
    printf("%04lx", address); 
}

void print_byte_row(page_format* format) {
    for (uint8_t count = 0; count < format->row_format.bytes_len; ++count) {
        string* byte_str = find_converter(format->byte_format.type, format->current_row[count]);
        printf("%s%c",
                byte_str->string,
                format->row_format.bytes_delimiter);
    }
}

void decode_print_row(page_format* format) {
    for (uint8_t count = 0; count < format->row_format.bytes_len; ++count) {
        char symb = decode_symb(format->current_row[count], format);

        printf("%c", symb);
    }
}


