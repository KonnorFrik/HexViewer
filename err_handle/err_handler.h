#ifndef __ERROR_HANDLER_H__
#define __ERROR_HANDLER_H__

#define START 10
#define OFFSET_SECTION 10

typedef enum {
    UNKNOWN_ERROR = -1,
    NO_ERROR = 0,

    //memory error's
    MEMORY_ERROR = START,
    ALLOC_ERROR,
    REALLOC_ERROR,

    //new_sect_err = prev_start_of_section + OFFSET_SECTION,
    WRONG_ARG_ERROR = MEMORY_ERROR + OFFSET_SECTION,
    CMD_ARG_ERROR,
    FUNC_ARG_ERROR,

    //IO_ERROR

} error_code;

int rough_is_null(void* ptr);  // exit or return status
int soft_is_null(void* ptr);   // return status

#endif
