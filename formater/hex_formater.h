/**
 * @file
 * @brief Contains functions prototypes for processing format struct
 */

#ifndef __BIN_TO_HEX_H__
#define __BIN_TO_HEX_H__

#include "types.h"
#include "../str_wrap/wrap.h"
#include <stdint.h>

/**
 * @brief Create format with rules and set default setting's
 * @note Alloc memory for page_format type
 * @return obj - default page_format object ptr */
page_format* page_format_create();

/**
 * @brief Free given page_format object 
 * @param[in] obj - NON NULL page_format object for free
 * @return void */
void page_format_destroy(page_format* obj);

/**
 * @brief Set values from cmd flags 
 * @note Call once on start of programm
 * @warning Do not allocate memory for obj if it NULL
 * @param[in]  argc - count of cmd argument's 
 * @param[in]  argv - cmd argument's
 * @param[out] obj - NON NULL page_format object for set flags
 * @return status - NO_ERROR, ERROR */
int page_format_init(int argc, char* const* argv, page_format* obj);

#endif

