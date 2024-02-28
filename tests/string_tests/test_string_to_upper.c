#include "string_tests.h"
#define NAME "\033[38;5;46m string \033[0m \033[38;5;45m to upper \033[0m"

START_TEST(string_to_upper_test_1) {
    string* str = string_create_from("HELlo");
    size_t result = string_to_upper(str);

    ck_assert_uint_eq(result, 2);
    ck_assert_str_eq(str->string, "HELLO");

    string_destroy(str);
}
END_TEST

START_TEST(string_to_upper_test_2) {
    string* str = string_create_from("hello");
    size_t result = string_to_upper(str);

    ck_assert_uint_eq(result, 5);
    ck_assert_str_eq(str->string, "HELLO");

    string_destroy(str);
}
END_TEST

START_TEST(string_to_upper_test_3) {
    string* str = string_create_from("");
    size_t result = string_to_upper(str);

    ck_assert_uint_eq(result, 0);
    ck_assert_str_eq(str->string, "");

    string_destroy(str);
}
END_TEST

START_TEST(string_to_upper_test_4) {
    string* str = NULL;
    size_t result = string_to_upper(str);

    ck_assert_uint_eq(result, 0);
}
END_TEST

Suite* test_string_to_upper() {
    Suite* su = suite_create(NAME);
    TCase* test_case = tcase_create(NAME);

    tcase_add_test(test_case, string_to_upper_test_1);
    tcase_add_test(test_case, string_to_upper_test_2);
    tcase_add_test(test_case, string_to_upper_test_3);
    tcase_add_test(test_case, string_to_upper_test_4);

    suite_add_tcase(su, test_case);

    return su;
}


