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
 * @brief Call needed file printer depends on flags in format
 * @param[in] filename Filename for open
 * @param[in] format page_format struct with rules
 * @return void
 */
static void file_printer(char* filename, page_format* format);

/**
 * @brief Print address, row of bytes, decoded symbols
 * @param[in] address Current address
 * @param[in] format page_format object with bytes and rules for print
 * @return void
 */
static void print_content(uint64_t address, page_format* format);

/**
 * @brief Return size of given file in bytes
 * @param[in] file File object to measure length
 * @return len in bytes
 */
static size_t file_len(FILE* file);

/**
 * @brief Set given offset to file if offset less then file len
 * @param[in,out] file File object for set in
 * @param[in]     offset Needed offset for start read from
 * @return status - NO_ERROR, ERROR
 */
static int safe_set_offset(FILE* file, uint32_t offset);

/** 
 * @brief Read whole file row by row and print
 * @param[in] filename Filename for print as hex
 * @param[in] format Struct with rules how print file
 * @return void
 */
static void print_file(FILE* file, page_format* format);

/** 
 * @brief Read whole file row by row and print rows if bytes in can be decoded to symbols
 * @param[in] filename Filename for print as hex
 * @param[in] format Struct with rules how print file
 * @return void
 */
static void print_files_strings(FILE* file, page_format* format);

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
            file_printer(argv[index], format);
        }

    }

    page_format_destroy(format);
    return ret_code;
}

static void file_printer(char* filename, page_format* format) {
    FILE* file = fopen(filename, "r");
    int status = NO_ERROR;

    if (file != NULL &&
        (status = safe_set_offset(file, format->offset)) != ERROR) {
        if (format->row_format.strings == 1) {
            print_files_strings(file, format);

        } else {
            print_file(file, format);
        }

    } else if (status == ERROR) {
        fprintf(stderr, "Given offset: '%u' too big for file: '%s'\tSkip file\n", format->offset, filename);

    } else {
        fprintf(stderr, "File: '%s' can't be opened\n", filename);
    }

    if (file != NULL) {
        fclose(file);
    }
}

static void print_file(FILE* file, page_format* format) {
        uint64_t address = 0;

        while (read_row(file, format) == format->row_format.bytes_len) {
            print_content(address, format);
            address += format->row_format.bytes_len;
        }
}

static void print_files_strings(FILE* file, page_format* format) {
    uint64_t address = 0;

    while (read_row(file, format) == format->row_format.bytes_len) {
        for (int i = 0; i < format->row_format.bytes_len; ++i) {
            if (decode_symb(format->current_row[i], format) != format->row_format.std_symbol) {
                print_content(address, format);
                break;
            }
        }

        address += format->row_format.bytes_len;
    }
}

static void print_content(uint64_t address, page_format* format) {
    printf("|");
    print_address(address, format);
    printf("  |  ");
    print_byte_row(format);
    printf("  |  ");
    decode_print_row(format);
    printf("|\n");
}

static size_t file_len(FILE* file) {
    long int current = ftell(file);
    fseek(file, 0, SEEK_END);
    size_t len = ftell(file);
    fseek(file, current, SEEK_SET);
    return len;
}

static int safe_set_offset(FILE* file, uint32_t offset) {
    if (file_len(file) < offset) {
        return ERROR;
    }

    fseek(file, offset, SEEK_SET);
    return NO_ERROR;
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
    printf("| --row-len <number>        - Read and print given count of bytes      |\n");
    printf("|                                   min/max: 1, 255 (default: 16)      |\n");
    printf("| --strings                 - Print row only if any byte can be        |\n");
    printf("|                                             printed as symbol        |\n");
    printf("| --help                    - Show this page                           |\n");
    printf("+----------------------------------------------------------------------+\n");
    //printf("|\n");
}

static void print_usage(char* programm_name) {
    printf("Usage: %s filename [flags]\n", programm_name);
}
