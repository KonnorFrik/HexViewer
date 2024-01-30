#ifndef __STRING_TESTS_H__
#define __STRING_TESTS_H__

#include <check.h>
#include <stdio.h>
#include "../../str_wrap/wrap.h"
#include "../common.h"

Suite* test_string_create();

Suite* test_string_write();
Suite* test_string_cat();

Suite* test_str_write();
Suite* test_str_cat();

Suite* test_string_destroy();

#endif
