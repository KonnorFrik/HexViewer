/**
 * @file
 * @brief Contains functions implementation for processing format struct
 */

#include "hex_formater.h"
#include "../err_handle/err_handler.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include <stdio.h>

#define NO_ARG 0
#define REQ_ARG 1

#define BYTE_PY_TYPE "python"
#define BYTE_PY_TYPE_SHORT "py"

#define OCT_ADDR_TYPE "oct"
#define DEC_ADDR_TYPE "dec"

/// @brief Numbers for flags for getopt
enum cmd_flags_ {
    fake = 0,
    help_flag,           ///< --help
    upper_case_flag,     ///< --upper-byte - Print bytes in upper case
    byte_type_flag,      ///< --byte-type <c, py(python)> - Print bytes in given type
    address_len_flag,    ///< --address-len <number> (min: 1, max: 255) - Print address with given length
    address_type_flag,   ///< --address-type <hex, dec, oct> - Print address in given type
    non_decode_flag,     ///< --non-decode <symb> - Print given symbol as non-decoding byte
    byte_delimiter_flag, ///< --byte-delimiter <symb> - Print given symbol between bytes
};

static void page_format_init_default(page_format* obj);
/* Set default values in page_format object 
 * ! Overwrite object
 * 1:   obj - page_format object ptr for init
 * ret: void */

int page_format_init(int argc, char* const* argv, page_format* obj) {
    if (argv == NULL || obj == NULL) {
        return ERROR;
    }

    int status = NO_ERROR;
    int long_index = -1;
    int cmd_flag = 0;
    char symb = 0;

    const char* short_names = "";
    const struct option long_names[] = {
        {"help", NO_ARG, &cmd_flag, help_flag},
        {"upper-byte", NO_ARG, &cmd_flag, upper_case_flag},

        {"byte-type", REQ_ARG, &cmd_flag, byte_type_flag},
        {"address-len", REQ_ARG, &cmd_flag, address_len_flag},
        {"address-type", REQ_ARG, &cmd_flag, address_type_flag},
        {"non-decode", REQ_ARG, &cmd_flag, non_decode_flag},
        {"byte-delimiter", REQ_ARG, &cmd_flag, byte_delimiter_flag},
        {0, 0, 0, 0}
    };

    opterr = 0;

    while (status == NO_ERROR && (symb = getopt_long(argc, argv, short_names, long_names, &long_index) != -1)) {
        //printf("symb:      '%c'(%d)\n", symb, symb);
        //printf("long_index: %d\n", long_index);
        //printf("cmd_flag:   %d\n", cmd_flag);
        //printf("optarg:     %s\n", optarg);
        //printf("optind:     %d\n", optind);
        //printf("\n");
        //switch (symb) {
            //case 'h':
                //printf("SHORT HELP FLAG\n");
                //obj->show_help = 1;
                //break;
        //}

        switch (cmd_flag) {
            case help_flag:
                obj->show_help = 1;
                break;

            case upper_case_flag:
                obj->byte_format.is_upper = 1;
                break;

            case byte_type_flag:
                if (strcmp(optarg, BYTE_PY_TYPE) == 0 ||
                    strcmp(optarg, BYTE_PY_TYPE_SHORT) == 0) {
                    obj->byte_format.type = py_type;
                } 
                break;

            case address_len_flag:
                obj->row_format.address_len = strtol(optarg, 0, 10);
                break;

            case address_type_flag:
                if (strcmp(optarg, DEC_ADDR_TYPE) == 0) {
                    obj->row_format.address_type = dec_type;

                } else if (strcmp(optarg, OCT_ADDR_TYPE) == 0) {
                    obj->row_format.address_type = oct_type;
                }
                break;

            case non_decode_flag:
                obj->row_format.std_symbol = optarg[0];
                break;

            case byte_delimiter_flag:
                obj->row_format.bytes_delimiter = optarg[0];
                break;

            //case '?':
                //fprintf(stderr, "Unknown argument, need exit\n");
                //status = ERROR;
                //break;

            default:
                fprintf(stderr, "Unknown error\n");
                status = ERROR;
                break;
        }
    }

    return status;
    //TODO postinit for allocate current_row with correct size stored in obj->...bytes_len
}

static void page_format_init_default(page_format* obj) {
    // [BYTE]
    obj->byte_format.is_upper = 0;
    obj->byte_format.type = c_type;

    // [ROW]
    obj->row_format.address_len = 4;
    obj->row_format.address_type = hex_type;
    obj->row_format.bytes_len = DEFAULT_ROW_LEN;
    obj->row_format.bytes_delimiter = ' ';
    obj->row_format.std_symbol = '.';

    // [PAGE]
    obj->is_show_header = 1;
    obj->header_every = 0;
}

page_format* page_format_create() {
    page_format* obj = 0;
    obj = calloc(1, sizeof(page_format));
    assert(obj != 0 && "Can't allocate memory");

    obj->current_row = calloc(DEFAULT_ROW_LEN,
                                  sizeof(uint8_t));

    assert(obj->current_row != 0 && "Can't allocate memory");

    // default init
    page_format_init_default(obj);

    return obj;
}

void page_format_destroy(page_format* obj) {
    if (!soft_is_null(obj)) {
        if (!soft_is_null(obj->current_row)) {
            free(obj->current_row);
        }

        free(obj);
    }
}

