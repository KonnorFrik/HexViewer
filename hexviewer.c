/**
 * @file
 * @brief Entry point
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
 * @brief Read whole file row by row and print
 * @param[in] filename Filename for print as hex
 * @param[in] format Struct with rules how print file
 * @return void
 */
static void print_file(char* filename, page_format* format);

/**
 * @brief Print help message
 * @return void */
static void print_help(char* programm_name);

/**
 * @brief Print usage 
 * @return void */
static void print_usage(char* programm_name);

/**
 * @brief Main function - Entry point
 * @param[in] argc Command line argument count
 * @param[in] argv Command line argument values
 * @return Programm status code
 */
int main(int argc, char* const* argv) {
//TODO mb compile all modules in one shared obj
    error_code ret_code = NO_ERROR;

    page_format* format = 0;
    format = page_format_create();
    page_format_init(argc, argv, format);

    if (format->show_help) {
        print_help(argv[0]);

    } else {
        if (optind >= argc) {
            fprintf(stderr, "No filename given for read\n");
            print_usage(argv[0]);
            ret_code = CMD_ARG_ERROR;
        }

        for (int index = optind; index < argc; ++index) {
            print_file(argv[index], format);
        }

    }

    page_format_destroy(format);
    return ret_code;
}

static void print_help(char* programm_name) {
    print_usage(programm_name);
    printf("                                Flags:\n");
    printf("+----------------------------------------------------------------------+\n");
    printf("|                 Byte format                                          |\n");
    printf("| --upper-byte              - Print bytes in upper case                |\n");
    printf("| --byte-type <type>        - Print bytes in given type                |\n");
    printf("|                                     (default: c-type)                |\n");
    printf("| --byte-delimiter <symb>   - Print given symbol between bytes         |\n");
    printf("|                                               (default: ' ')         |\n");
    printf("|                                                                      |\n");
    printf("|                 Row format                                           |\n");
    printf("| --address-len <number>    - Print address with given length          |\n");
    printf("|                                 min/max printable - address in hex   |\n");
    printf("|                                 min/max valid - 1 - 255              |\n");
    printf("| --address-type <type>     - Print address in given type              |\n");
    printf("|                                          (default: hex)              |\n");
    printf("| --non-decode <symb>       - Print given symbol as non-decoding byte  |\n");
    printf("| --help    - Show this page                                           |\n");
    printf("+----------------------------------------------------------------------+\n");
    //printf("|\n");
}

static void print_usage(char* programm_name) {
    printf("Usage: %s filename [flags]\n", programm_name);
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
