#include "hex_formater.h"
#include "../err_handle/err_handler.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

char decode_symb(uint8_t symb, page_format* obj) {
    char result = obj->row_format.std_symbol;

    if (symb > 31 && symb < 127) {
        result = (char)symb;
    }

    return result;
}

void decode_row(page_format* obj, string* decoded_line) {
    uint32_t buf_size = obj->row_format.bytes_len + 1;
    char buffer[buf_size];
    memset(buffer, 0, buf_size);

    for (uint32_t i = 0; i < buf_size; ++i) {
        buffer[i] = decode_symb(obj->current_row[i], obj);
    }

    str_write(decoded_line, buffer);
}

page_format* page_format_create() {
    page_format* obj = calloc(1, sizeof(page_format));

    // default init
    if (!soft_is_null(obj)) {
        // [BYTE]
        obj->byte_format.type = c_type;

        // [ROW]
        obj->row_format.address_len = 4;
        obj->row_format.address_type = hex_type;
        obj->row_format.bytes_len = 16;
        obj->row_format.bytes_delimiter = ' ';
        obj->row_format.std_symbol = '.';

        // [PAGE]
        obj->is_show_header = 1;
        obj->current_row = calloc(obj->row_format.bytes_len, sizeof(uint8_t));
    }

    assert(obj && "Can't allocate memory");
    assert(obj->current_row && "Can't allocate memory");

    return obj;
}

void page_format_destroy(page_format* obj) {
    if (!soft_is_null(obj)) {
        free(obj);
    }
}

