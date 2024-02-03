#ifndef __HEX_VIEWS_H__
#define __HEX_VIEWS_H__

#include "../formater/types.h"
#include "../str_wrap/wrap.h"
#include <stdint.h>

char decode_symb(uint8_t symb, page_format* obj);
/* Return symbol for print 
 * If symb non-printable - return default symbol
 * 1:   symb - byte for decode
 * 2:   obj - page_format object ptr
 * ret: decoded - always printable char */

void decode_row(page_format* obj, string* decoded_line);
/* Decode current n bytes and write in string object
 * 1:   obj - page_format object ptr with bytes
 * 2:   decoded_line - string object ptr for write
 * ret: void */

void print_byte_row(page_format* format);
/* Print n bytes from page_format object with rules
 * 1:   format - page_format object ptr with bytes and rules
 * ret: void */

void decode_print_row(page_format* format);
/* Decode bytes in page_format obj with rules and print 
 * 1:   format - page_format object ptr with bytes and rules 
 * ret: void */

void print_address(uint64_t address, page_format* format);
/* Print given address with rules in page_format object 
 * 1:   address - address for print
 * 2:   format - page_format object ptr with rules
 * ret: void */

#endif
