/**
 * \file
 * \brief Entry point
 * Contains main function and some auxiliary
 */

#include "views/views.h"
#include "formater/hex_formater.h"
#include "str_wrap/wrap.h"
#include "data/data_processing.h"
#include "err_handle/err_handler.h"
#include <getopt.h>
#include <stdio.h>

/** 
 * \brief Read whole file row by row and print
 * \param[in] filename Filename for print as hex
 * \param[in] format Struct with rules how print file
 * \return void
 */
static void print_file(char* filename, page_format* format);

/**
 * \brief Print help message
 * \return void */
static void print_help();

/**
 * \brief Print usage 
 * \return void */
static void print_usage();

/**
 * \brief Main function - Entry point
 * \param[in] argc Command line argument count
 * \param[in] argv Command line argument values
 * \return Programm status code
 */
int main(int argc, char* const* argv) {
//TODO mb compile all modules in one shared obj
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

static void print_help() {
    printf("HELP PAGE\n");
}

static void print_usage() {
    printf("USAGE\n");
}

static void print_file(char* filename, page_format* format) {
    FILE* file = fopen(filename, "r");

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
