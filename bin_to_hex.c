#include "bin_to_hex.h"
#include <stdint.h>

typedef enum _byte_type {
    no-type = 0
    c-type,
    py-type,
} byte_type;

typedef enum _addr_type {
    hex-type = 1,
    dec-type,
} addr_type;

typedef struct _byte_format {
    /* Describe which format use for print byte, indent after byte*/
    uint8_t is_upper: 1;
    uint8_t reserve: 7;
    byte_type type;
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
} page_format;

static char decode_symb(unsigned char symb);

static char decode_symb(unsigned char symb) {
    char result = '.';

    // mb isgraph will be better
    // need check only is symb printable as normal symb
    if (symb > 31 && symb < 127) {
        result = (char)symb;
    }

    return result;
}

