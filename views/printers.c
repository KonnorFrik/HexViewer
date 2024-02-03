#include "views.h"
#include <stdio.h>

void print_address(uint64_t address, page_format* format) {
    printf("%4lx", address); 
}

void print_byte_row(page_format* format) {
    for (uint8_t count = 0; count < format->row_format.bytes_len; ++count) {
        printf("%02x%c",
                format->current_row[count],
                format->row_format.bytes_delimiter);
    }
}

void decode_print_row(page_format* format) {
    for (uint8_t count = 0; count < format->row_format.bytes_len; ++count) {
        char symb = decode_symb(format->current_row[count], format);

        printf("%c", symb);
    }
}


