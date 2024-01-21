#ifndef __STRING_TESTS_H__
#define __STRING_TESTS_H__

#define TEST_PRINT 1

#if TEST_PRINT == 1
    #include <stdio.h>
#endif

#include <check.h>
#include <stdio.h>
#include "../../str_wrap/wrap.h"

Suite* test_string_create();

Suite* test_string_write();
Suite* test_string_cat();

Suite* test_str_write();
Suite* test_str_cat();

Suite* test_string_destroy();

#endif
