#include "views/views.h"
#include "formater/hex_formater.h"
#include "str_wrap/wrap.h"

#include <stdio.h>
#include <assert.h>

size_t read_bytes(FILE* file, page_format* format_out);
/* Read n bytes from given file in buffer in page_format
 * i Count of bytes store in page_format object 
 * 1:   file - file for read from
 * 2:   format_out - page_format object ptr with rules and out buffer
 * ret: count - of readed bytes */

void print_file(char* filename, page_format* format);
/* Read whole file row by row and print page with rules
 * 1:   filename - filename for read
 * 2:   format - page_format object ptr with rules
 * ret: void */

size_t read_bytes(FILE* file, page_format* format_out) {
    size_t readed = fread(format_out->current_row,
                          1,
                          format_out->row_format.bytes_len,
                          file);
    return readed;
}

void print_file(char* filename, page_format* format) {
    FILE* file = fopen(filename, "r");
    assert(file && "Can't open file");

    uint64_t address = 0;

    while (read_bytes(file, format) == format->row_format.bytes_len) {
        printf("|  ");
        print_address(address, format);
        printf("  |  ");
        print_byte_row(format);
        printf("  |  ");
        decode_print_row(format);
        printf("  |\n");
        address += format->row_format.bytes_len;
    }

    fclose(file);
}

int main() {
    char* filename = "hexviewer";
    page_format* format = page_format_create();
    print_file(filename, format);
    page_format_destroy(format);
    return 0;
}
