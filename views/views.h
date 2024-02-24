/**
 * \file
 * \brief Header of data output module
 *
 * Contains print functions prototypes
 */

#ifndef __HEX_VIEWS_H__
#define __HEX_VIEWS_H__

#include "../formater/types.h"
#include "../str_wrap/wrap.h"
#include <stdint.h>

/**
 * \brief Decode given byte with given rules 
 * If symb non-printable - return default symbol
 * \param[in] symb Byte for decode
 * \param[in] obj Page_format object with rules
 * \return decoded_symbol - always printable char */
char decode_symb(uint8_t symb, page_format* obj);

//TODO move up and down prototypes in data

/**
 * \brief Decode current n bytes and write in string object
 * \param[in] obj Page_format object with bytes array
 * \param[out] decoded_line String object for write result
 * \return void */
void decode_row(page_format* obj, string* decoded_line);

/**
 * \brief Print n bytes from page_format object with rules
 * \param[in] format Page_format object with bytes and rules
 * \return void */
void print_byte_row(page_format* format);

/**
 * \brief Decode bytes stored in page_format obj with rules and print 
 * \param[in] format Page_format object with bytes for print and rules for apply
 * \return void */
void decode_print_row(page_format* format);

/**
 * \brief Print address in given format
 * \param[in] address Address for print
 * \param[in] format Page_format object with rules
 * \return void */
void print_address(uint64_t address, page_format* format);

/**
 * \brief Find converter for given type and run it with given arg
 * \param[in] search Converter type for search 
 * \param[in] byte Data for convert
 * \param[out] buffer_out String ptr for write result
 * \return byte_str - string object ptr, same as buffer_out */
string* convert_byte_to_str(byte_type search, uint8_t byte, string* buffer_out);

#endif
