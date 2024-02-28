/**
 * @file
 * @brief Contains functions for reader aka data-getters
 */

#include "data_processing.h"
#include "string.h"

size_t read_row(FILE* file, page_format* format_out) {
    memset(format_out->current_row, 0, format_out->row_format.bytes_len);

    size_t readed = fread(format_out->current_row,
                          1,
                          format_out->row_format.bytes_len,
                          file);
    return readed;
}

