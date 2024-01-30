#ifndef __BIN_TO_HEX_H__
#define __BIN_TO_HEX_H__


page_format* create_page_format();
/* Alloc memory for page_format type
 * Set default setting's 
 * ret: obj - default page_format object ptr */

void destroy_page_format(page_format* obj);
/* Free given page_format object 
 * 1:   obj - NON NULL page_format object ptr for free
 * ret: void */

#endif

