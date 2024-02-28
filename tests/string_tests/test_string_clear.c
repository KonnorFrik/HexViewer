#include "string_tests.h"
#define NAME "\033[38;5;46m string \033[0m \033[38;5;45m clear \033[0m"

START_TEST(string_clear_test_1) {
    string* obj = string_create();
    char* str = "HELLO";
    str_write(obj, str);

    ck_assert_str_eq(obj->string, str);

    string_clear(obj);

    ck_assert_str_eq(obj->string, "");

    string_destroy(obj);
}
END_TEST

Suite* test_string_clear() {
    Suite* su = suite_create(NAME);
    TCase* test_case = tcase_create(NAME);

    tcase_add_test(test_case, string_clear_test_1);

    suite_add_tcase(su, test_case);

    return su;
}

