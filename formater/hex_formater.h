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

#endif

