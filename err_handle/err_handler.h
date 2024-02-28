/**
 * @file
 * @brief Contains struct with error codes and functions prototypes
 */

#ifndef __ERROR_HANDLER_H__
#define __ERROR_HANDLER_H__

#define START 10
#define OFFSET_SECTION 10

/// @brief Error codes for the whole programm
typedef enum {
    ERROR = -1,          ///< Common Error
    NO_ERROR = 0,        ///< aka OK

    //memory error's
    MEMORY_ERROR = START, ///< Common code for any memory error
    ALLOC_ERROR,          ///< Problem with memory allocation
    REALLOC_ERROR,        ///< Problem with memory re-allocation

    //new_sect_err = prev_start_of_section + OFFSET_SECTION,
    WRONG_ARG_ERROR = MEMORY_ERROR + OFFSET_SECTION, ///< Common code for any error with arguments
    CMD_ARG_ERROR,                                   ///< Problem with arguments from command line
    FUNC_ARG_ERROR,                                  ///< Problem with function arguments

    //IO_ERROR

} error_code;

/**
 * @brief Check given ptr for NULL
 * @warning Immediately abort all programm if ptr is NULL
 * @param[in] ptr Pointer for check
 * @return status - NO_ERROR
 */
int rough_is_null(void* ptr);

/**
 * @brief Check given ptr for NULL
 * @param[in] ptr Pointer for check
 * @return status - NO_ERROR, ERROR
 */
int soft_is_null(void* ptr);

#endif
