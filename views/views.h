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

#endif
