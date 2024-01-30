#ifndef __BIN_TO_HEX_H__
#define __BIN_TO_HEX_H__

#include "types.h"
#include "../str_wrap/wrap.h"
#include <stdint.h>

page_format* page_format_create();
/* Alloc memory for page_format type
 * Set default setting's 
 * ret: obj - default page_format object ptr */

void page_format_destroy(page_format* obj);
/* Free given page_format object 
 * 1:   obj - NON NULL page_format object ptr for free
 * ret: void */

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

#endif

