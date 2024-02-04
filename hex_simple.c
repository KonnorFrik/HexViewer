#include "views/views.h"
#include "formater/hex_formater.h"
#include "str_wrap/wrap.h"
#include "data/readers.h"

#include <stdio.h>
#include <assert.h>

void print_file(char* filename, page_format* format);
/* Read whole file row by row and print page with rules
 * i For non-interactive mode
 * 1:   filename - filename for read
 * 2:   format - page_format object ptr with rules
 * ret: void */

void print_file(char* filename, page_format* format) {
    FILE* file = fopen(filename, "r");
    assert(file && "Can't open file");

    uint64_t address = 0;

    while (read_row(file, format) == format->row_format.bytes_len) {
        // TODO make smthng with it '|'
        printf("|");
        print_address(address, format);
        printf("  |  ");
        print_byte_row(format);
        printf("  |  ");
        decode_print_row(format);
        printf("|\n");
        address += format->row_format.bytes_len;
    }

    fclose(file);
}

int main() {
    char* filename = "pattern_design.txt";
    page_format* format = page_format_create();
    format->byte_format.type = py_type;

    print_file(filename, format);
    page_format_destroy(format);
    return 0;
}
