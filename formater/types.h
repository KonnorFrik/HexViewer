/** @file 
 *  @brief Header with format rules struct implementation
 */

#ifndef __FORMAT_TYPES_H__
#define __FORMAT_TYPES_H__

#include <stdint.h>

#define DEFAULT_ROW_LEN 16

/// @brief types for describe how print byte
typedef enum byte_type_ {
    no_type = 0,
    c_type,
    py_type,
    type_end, // not for users, need delete this and 'no_type'
} byte_type;

/// @brief types for describe how print address number
typedef enum addr_type_ {
    hex_type = 1,
    dec_type,
    oct_type,
} addr_type;

/// @brief store rules for processing and print one byte from row
typedef struct byte_format_ {
    uint8_t is_upper: 1;     ///< @note default: lower
    uint8_t reserve: 7;
    byte_type type;          ///< @note default: c-type
} byte_format;

/// @brief store rules for processing and print row of bytes
typedef struct row_format_ {
    uint8_t address_len;     ///< @note default: 4
    addr_type address_type ; ///< @note default: hex 

    uint8_t bytes_len;       ///< @note default: 16 
    char bytes_delimiter;    ///< @note default: ' '

    //uint8_t symbs_len;   // as bytes_len
    char std_symbol;         ///< @note default: '.'
} row_format;

/// @brief store rules for processing and print page
typedef struct page_format_ {
    uint8_t is_show_header: 1; ///< Should header be printed default: 1
    uint8_t show_help: 1;      ///< Is show help message default: 0(NO) - turn on only if given flag '--help'
    uint8_t reserve: 6;
    uint32_t header_every;     ///< Print page header every n rows, Default: print once, may be changed with flag
    byte_format byte_format;   ///< See: @link byte_format_
    row_format row_format;     ///< See: @link row_format_
    uint8_t* current_row;      ///< store current 'row_format.bytes_len' bytes from file
} page_format;

#endif
