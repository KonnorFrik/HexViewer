#ifndef __HEX_READER_H__
#define __HEX_READER_H__

#include <stdio.h>
#include "../formater/types.h"
#include "../str_wrap/wrap.h"

size_t read_row(FILE* file, page_format* format_out);
/* Read n bytes from given file in buffer in page_format
 * i Count of bytes store in page_format object 
 * 1:   file - file for read from
 * 2:   format_out - page_format object ptr with rules and out buffer
 * ret: count - of readed bytes */

/**
 * \brief Decode given byte with given rules 
 * If symb non-printable - return default symbol
 * \param[in] symb Byte for decode
 * \param[in] obj Page_format object with rules
 * \return decoded_symbol - always printable char */
char decode_symb(uint8_t symb, page_format* obj);

/**
 * \brief Decode current n bytes and write in string object
 * \param[in] obj Page_format object with bytes array
 * \param[out] decoded_line String object for write result
 * \return void */
void decode_row(page_format* obj, string* decoded_line);

/**
 * \brief Find converter for given type and run it with given arg
 * \param[in] search Converter type for search 
 * \param[in] byte Data for convert
 * \param[out] buffer_out String ptr for write result
 * \return byte_str - string object ptr, same as buffer_out */
string* convert_byte_to_str(byte_type search, uint8_t byte, string* buffer_out);

#endif
