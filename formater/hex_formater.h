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

void page_format_init(int argc, char* const* argv, page_format* obj);
/* Set values from cmd args 
 * 1:   argc - count of cmd argument's 
 * 2:   argv - cmd argument's
 * 3:   obj - page_format object ptr for init
 * ret: void */

#endif

