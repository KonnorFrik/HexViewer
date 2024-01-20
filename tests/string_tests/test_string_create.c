#include "string_tests.h"
#define NAME "\033[38;5;46m string \033[0m \033[38;5;45m create \033[0m"

START_TEST(string_create_test_1) {
    string* obj = string_create();

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->string);
    ck_assert_int_eq(obj->size, 1);

    string_destroy(obj);
}
END_TEST

START_TEST(string_create_from_null) {
    string* obj = string_create_from(0);

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->string);
    ck_assert_int_eq(*obj->string, 0);

    string_destroy(obj);
}
END_TEST

START_TEST(string_create_from_str_1) {
    char* str = "A";
    string* obj = string_create_from(str);

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->string);
    ck_assert_str_eq(obj->string, str);
    ck_assert_uint_eq(obj->length, 1);
    ck_assert_uint_eq(obj->size, 2);

    string_destroy(obj);
}
END_TEST

START_TEST(string_create_from_str_empty) {
    char* str = "";
    string* obj = string_create_from(str);

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->string);
    ck_assert_str_eq(obj->string, str);
    ck_assert_uint_eq(obj->length, 0);
    ck_assert_uint_eq(obj->size, 1);

    string_destroy(obj);
}
END_TEST

Suite* test_string_create() {
    Suite* su = suite_create(NAME);
    TCase* test_case = tcase_create(NAME);

    tcase_add_test(test_case, string_create_test_1);
    tcase_add_test(test_case, string_create_from_null);
    tcase_add_test(test_case, string_create_from_str_1);
    tcase_add_test(test_case, string_create_from_str_empty);

    suite_add_tcase(su, test_case);

    return su;
}
