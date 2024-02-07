#include "hex_formater.h"
#include "../err_handle/err_handler.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#include <stdio.h>

#define NO_ARG 0
#define REQ_ARG 1

enum _cmd_flags {
    fake = 0,
    upper_case_flag,
};

static void page_format_init_default(page_format* obj);
/* Set default values in page_format object 
 * ! Overwrite object
 * 1:   obj - page_format object ptr for init
 * ret: void */

void page_format_init(int argc, char* const* argv, page_format* obj) {
    int long_index = -1;
    int cmd_flag = 0;
    char symb = 0;

    const char* short_names = "";
    const struct option long_names[] = {
        {"upper-byte", NO_ARG, &cmd_flag, upper_case_flag},
        {0, 0, 0, 0}
    };

    opterr = 0;

    while ((symb = getopt_long(argc, argv, short_names, long_names, &long_index) != -1)) {
        //printf("symb:      '%c'(%d)\n", symb, symb);
        //printf("long_index: %d\n", long_index);
        //printf("cmd_flag:   %d\n", cmd_flag);
        //printf("optarg:     %s\n", optarg);
        //printf("optind:     %d\n", optind);
        //printf("\n");
        switch (cmd_flag) {
            case upper_case_flag:
                obj->byte_format.is_upper = 1;
                break;

            case '?':
                printf("Unknown argument, need exit\n");
                break;

            default:
                printf("Unknown error\n");
                break;
        }
    }
}

static void page_format_init_default(page_format* obj) {
    // [BYTE]
    obj->byte_format.is_upper = 0;
    obj->byte_format.type = c_type;

    // [ROW]
    obj->row_format.address_len = 4;
    obj->row_format.address_type = hex_type;
    obj->row_format.bytes_len = 16;
    obj->row_format.bytes_delimiter = ' ';
    obj->row_format.std_symbol = '.';

    // [PAGE]
    obj->is_show_header = 1;
    obj->header_every = 0;
}

page_format* page_format_create() {
    page_format* obj = 0;
    obj = calloc(1, sizeof(page_format));

    if (!soft_is_null(obj)) {
        obj->current_row = calloc(obj->row_format.bytes_len,
                                  sizeof(uint8_t));
    }

    assert(obj && "Can't allocate memory");
    assert(obj->current_row && "Can't allocate memory");

    // default init
    page_format_init_default(obj);

    return obj;
}

void page_format_destroy(page_format* obj) {
    if (!soft_is_null(obj)) {
        free(obj);
    }
}

