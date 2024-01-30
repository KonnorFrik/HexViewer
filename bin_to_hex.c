#include "bin_to_hex.h"
#include <stdint.h>

typedef enum _byte_type {
    no_type = 0
    c_type,
    py_type,
} byte_type;

typedef enum _addr_type {
    hex_type = 1,
    dec_type,
    oct_type,
} addr_type;

typedef struct _byte_format {
    /* Describe which format use for print byte, indent after byte*/
    uint8_t is_upper: 1;
    uint8_t reserve: 7;
    byte_type type;     // c-type
} byte_format;

typedef struct _row_format {
    uint8_t address_len;    // 4 default
    addr_type addres_type ; // hex default

    uint8_t bytes_len;   // 16 default
    char bytes_delimiter; // ' '

    //uint8_t symbs_len;   // as bytes_len
    char std_symbol;     // '.'
} row_format;

typedef struct _page_format {
    uint8_t is_show_header: 1;
    uint8_t reserve: 7;
    uint32_t header_every; // 0 - print once, n - print if is_show
    row_format row_format;
    byte_format byte_format;
} page_format;

static char decode_symb(uint8_t symb);

static char decode_symb(uint8_t symb) {
    char result = '.';

    if (symb > 31 && symb < 127) {
        result = (char)symb;
    }

    return result;
}

page_format* create_page_format() {
    page_format* obj = calloc(1, sizeof(page_format));

    if (!soft_is_null(obj)) {
        // [BYTE]
        obj->byte_format->type = c_type;

        // [ROW]
        obj->row_format->address_len = 4;
        obj->row_format->address_type = hex_type;
        obj->row_format->bytes_len = 16;
        obj->row_format->bytes_delimiter = ' ';
        obj->row_format->std_symbol = '.';

        // [PAGE]
        obj->is_show_header = 1;
    }

    return obj;
}

void destroy_page_format(page_format* obj) {
    if (!soft_is_null(obj)) {
        free(obj);
    }
}
