#include "readers.h"

size_t read_row(FILE* file, page_format* format_out) {
    size_t readed = fread(format_out->current_row,
                          1,
                          format_out->row_format.bytes_len,
                          file);
    return readed;
}

