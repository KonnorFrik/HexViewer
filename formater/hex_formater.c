#include "hex_formater.h"
#include "../err_handle/err_handler.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

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

