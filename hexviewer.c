#include "views/views.h"
#include "formater/hex_formater.h"
#include "str_wrap/wrap.h"
#include "data/readers.h"

#include <getopt.h>
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
    //assert(file && "Can't open file");

    if (file != 0) {
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

    } else {
        fprintf(stderr, "File: '%s' can't be opened\n", filename);
    }
}

//TODO mb compile all modules in one shared obj
int main(int argc, char* const* argv) {
    page_format* format = 0;
    format = page_format_create();
    page_format_init(argc, argv, format);

    if (optind >= argc) {
        fprintf(stderr, "No filename given for read\n");
    }

    for (int index = optind; index < argc; ++index) {
        print_file(argv[index], format);
    }

    page_format_destroy(format);
    return 0;
}
