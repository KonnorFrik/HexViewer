#ifndef __FORMAT_TYPES_H__
#define __FORMAT_TYPES_H__

#include <stdint.h>

#define DEFAULT_ROW_LEN 16

typedef enum _byte_type {
    no_type = 0,
    c_type,
    py_type,
    type_end, // not for users
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
    addr_type address_type ; // hex default

    uint8_t bytes_len;   // 16 default
    char bytes_delimiter; // ' '

    //uint8_t symbs_len;   // as bytes_len
    char std_symbol;     // '.'
} row_format;

typedef struct _page_format {
    uint8_t is_show_header: 1;
    uint8_t reserve: 7;
    uint32_t header_every; // 0 - print once, n - print if is_show
    byte_format byte_format;
    row_format row_format;
    uint8_t* current_row; // store current n bytes from file
} page_format;

#endif
