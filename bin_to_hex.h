#ifndef __BIN_TO_HEX_H__
#define __BIN_TO_HEX_H__

void warr_to_hex(WINDOW* scr, unsigned char* arr, unsigned long count);
void wprintf_decoded_row(WINDOW* scr, unsigned char* arr, unsigned int start_addr, unsigned int count);

#endif