#include "string_tests.h"
#define NAME "\033[38;5;46m str \033[0m \033[38;5;45m    to upper \033[0m"

START_TEST(str_to_upper_test_1) {
    char str[] = "HELlo";
    size_t result = str_to_upper(str);

    ck_assert_uint_eq(result, 2);
    ck_assert_str_eq(str, "HELLO");
}
END_TEST

START_TEST(str_to_upper_test_2) {
    char str[] = "hello";
    size_t result = str_to_upper(str);

    ck_assert_uint_eq(result, 5);
    ck_assert_str_eq(str, "HELLO");
}
END_TEST

START_TEST(str_to_upper_test_3) {
    char str[] = "";
    size_t result = str_to_upper(str);

    ck_assert_uint_eq(result, 0);
    ck_assert_str_eq(str, "");
}
END_TEST

START_TEST(str_to_upper_test_4) {
    char str[] = "HELLO WoRlD";
    size_t result = str_to_upper(str);

    ck_assert_uint_eq(result, 2);
    ck_assert_str_eq(str, "HELLO WORLD");
}
END_TEST

START_TEST(str_to_upper_test_5) {
    char* str = NULL;
    size_t result = str_to_upper(str);

    ck_assert_uint_eq(result, 0);
}
END_TEST

Suite* test_str_to_upper() {
    Suite* su = suite_create(NAME);
    TCase* test_case = tcase_create(NAME);

    tcase_add_test(test_case, str_to_upper_test_1);
    tcase_add_test(test_case, str_to_upper_test_2);
    tcase_add_test(test_case, str_to_upper_test_3);
    tcase_add_test(test_case, str_to_upper_test_4);
    tcase_add_test(test_case, str_to_upper_test_5);

    suite_add_tcase(su, test_case);

    return su;
}

