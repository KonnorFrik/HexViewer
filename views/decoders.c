#include "views.h"
#include <string.h>

char decode_symb(uint8_t symb, page_format* obj) {
    char result = obj->row_format.std_symbol;

    if (symb > 32 && symb < 127) {
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


