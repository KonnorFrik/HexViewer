#ifndef __HEX_READER_H__
#define __HEX_READER_H__

#include <stdio.h>
#include "../formater/types.h"

size_t read_row(FILE* file, page_format* format_out);
/* Read n bytes from given file in buffer in page_format
 * i Count of bytes store in page_format object 
 * 1:   file - file for read from
 * 2:   format_out - page_format object ptr with rules and out buffer
 * ret: count - of readed bytes */

#endif
