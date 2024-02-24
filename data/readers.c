#include "data_processing.h"

size_t read_row(FILE* file, page_format* format_out) {
    //TODO clear buffer
    size_t readed = fread(format_out->current_row,
                          1,
                          format_out->row_format.bytes_len,
                          file);
    return readed;
}

