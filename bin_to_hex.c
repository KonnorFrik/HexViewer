#include <ncurses.h>
#include "bin_to_hex.h"

typedef struct {
    /* Describe which format use for print byte, indent after byte*/
} ByteFormat;

static char decode_symb(unsigned char symb);

static char decode_symb(unsigned char symb) {
    char result = '.';

    // mb isgraph will be better
    // need check only is symb printable as normal symb
    if (symb > 31 && symb < 127) {
        result = (char)symb;
    }

    return result;
}

void wrow_to_hex(WINDOW* src, unsigned char* arr, unsigned long count) {
    /* Print next 'count' bytes from arr to given screnn 'scr' in hex 
     * 1:   scr - WINDOW object ptr for print on 
     * 2:   arr - array of bytes for print it
     * 3:   count - count for print
     * ret: void */

    //just print row in hex
    //No print address
    //No print \n
}

void warr_to_hex(WINDOW* scr, unsigned char* arr, unsigned long count) {
    /* Print 'count' bytes from arr of bytes to given screnn 'scr' in hex 
     * 1:   scr - WINDOW object ptr for print on 
     * 2:   arr - array of bytes for print it
     * 3:   count - count for print
     * ret: void */

    // while ind < size
    unsigned long address = 0;

    while (address < count) {
        // print addr
        address++;
    }
    // print byte's in hex
    // print aign if need
    // print decoded symb's
}
