#include "string_tests.h"
#define NAME "\033[38;5;46m string \033[0m \033[38;5;45m destroy \033[0m"

START_TEST(string_destroy_test_empty) {
    string* obj = string_create();

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->string);

    string* new_ptr = string_destroy(obj);

    ck_assert_ptr_nonnull(obj);

    ck_assert_ptr_null(new_ptr);
    ck_assert_ptr_ne(new_ptr, obj);
}
END_TEST

START_TEST(string_destroy_test_normal) {
    string* obj = string_create_from("Word");

    string* new_ptr = string_destroy(obj);

    ck_assert_ptr_nonnull(obj);

    ck_assert_ptr_null(new_ptr);
    ck_assert_ptr_ne(new_ptr, obj);
}
END_TEST

START_TEST(string_destroy_test_null) {
    string* obj = 0;

    string* new_ptr = string_destroy(obj);

    ck_assert_ptr_null(obj);

    ck_assert_ptr_null(new_ptr);
    ck_assert_ptr_eq(new_ptr, obj);
}
END_TEST

Suite* test_string_destroy() {
    Suite* su = suite_create(NAME);
    TCase* test_case = tcase_create(NAME);

    tcase_add_test(test_case, string_destroy_test_empty);
    tcase_add_test(test_case, string_destroy_test_normal);
    tcase_add_test(test_case, string_destroy_test_null);

    suite_add_tcase(su, test_case);

    return su;
}

