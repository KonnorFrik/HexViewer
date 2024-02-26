/**
 * @file
 * @brief Contains functions prototypes for 'data_processing' module
 */

#ifndef __HEX_READER_H__
#define __HEX_READER_H__

#include <stdio.h>
#include "../formater/types.h"
#include "../str_wrap/wrap.h"

/**
 * @brief Read n bytes from given file in buffer in page_format
 * @note Count of bytes store in page_format object 
 * @param[in]  file - file for read from
 * @param[out] format_out - page_format object ptr with rules and out buffer
 * @return count - of readed bytes */
size_t read_row(FILE* file, page_format* format_out);

/**
 * @brief Decode given byte with given rules 
 * If symb non-printable - return default symbol
 * @param[in] symb Byte for decode
 * @param[in] obj Page_format object with rules
 * @return decoded_symbol - always printable char */
char decode_symb(uint8_t symb, page_format* obj);

/**
 * @brief Decode current n bytes and write in string object
 * @param[in] obj Page_format object with bytes array
 * @param[out] decoded_line String object for write result
 * @return void */
void decode_row(page_format* obj, string* decoded_line);

/**
 * @brief Find converter for given type and run it with given arg
 * @param[in] search Type for convert in 
 * @param[in] byte Data for convert
 * @param[out] buffer_out String object for write result
 * @return byte_str - string object ptr, same as buffer_out */
string* convert_byte_to_str(byte_type search, uint8_t byte, string* buffer_out);

#endif
