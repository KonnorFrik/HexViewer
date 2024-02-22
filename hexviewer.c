#include "views/views.h"
#include "formater/hex_formater.h"
#include "str_wrap/wrap.h"
#include "data/readers.h"
#include "err_handle/err_handler.h"

#include <getopt.h>
#include <stdio.h>
#include <assert.h>

static void print_file(char* filename, page_format* format);
/* Read whole file row by row and print page with rules
 * i For non-interactive mode
 * 1:   filename - filename for read
 * 2:   format - page_format object ptr with rules
 * ret: void */

static void print_help();
/* Print help page
 * ret: void */

static void print_usage();
/* Print usage 
 * ret: void */


static void print_help() {
    printf("HELP PAGE\n");
}

static void print_usage() {
    printf("USAGE\n");
}

static void print_file(char* filename, page_format* format) {
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
    error_code ret_code = NO_ERROR;

    page_format* format = 0;
    format = page_format_create();
    page_format_init(argc, argv, format);

    if (format->show_help) {
        print_help();

    } else {
        if (optind >= argc) {
            fprintf(stderr, "No filename given for read\n");
            print_usage();
            ret_code = CMD_ARG_ERROR;
        }

        for (int index = optind; index < argc; ++index) {
            print_file(argv[index], format);
        }

    }

    page_format_destroy(format);
    return ret_code;
}
