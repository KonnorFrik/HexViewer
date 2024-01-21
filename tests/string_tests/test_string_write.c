#include "string_tests.h"
#define NAME "\033[38;5;46m string \033[0m \033[38;5;45m write \033[0m"

START_TEST(string_write_test_overwrite_empty_1) {
    string* str = string_create_from("Hello");
    string* obj = string_create();

    //#if TEST_PRINT == 1
    //printf("\n");
    //printf("\t[TEST_DEBUG]: Before write\n");
    //printf("\t[TEST_DEBUG]: obj.str   : '%s'\n", obj->string);
    //printf("\t[TEST_DEBUG]: obj.lenght: %lu\n", obj->length);
    //printf("\t[TEST_DEBUG]: obj.size  : %lu\n", obj->size);
    //#endif

    size_t writed = string_write(obj, str);

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->string);
    ck_assert_str_eq(obj->string, str->string);
    ck_assert_uint_eq(obj->length, 5);
    ck_assert_uint_eq(obj->size, 6);
    ck_assert_uint_eq(writed, 6);

    string_destroy(obj);
}
END_TEST

START_TEST(string_write_test_overwrite_str) {
    string* obj = string_create_from("Hello");
    string* str2 = string_create_from("edit");

    size_t writed = string_write(obj, str2);

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->string);
    ck_assert_str_eq(obj->string, str2->string);
    ck_assert_uint_eq(obj->length, 4);
    ck_assert_uint_eq(obj->size, 6);
    ck_assert_uint_eq(writed, 5);

    string_destroy(obj);
}
END_TEST

START_TEST(string_write_test_overwrite_with_empty) {
    string* obj = string_create_from("Hello");
    string* str2 = string_create_from("");

    size_t writed = string_write(obj, str2);

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->string);
    ck_assert_str_eq(obj->string, str2->string);
    ck_assert_uint_eq(obj->length, 0);
    ck_assert_uint_eq(obj->size, 6);
    ck_assert_uint_eq(writed, 1);

    string_destroy(obj);
}
END_TEST

START_TEST(string_write_test_overwrite_empty_2) {
    string* obj = string_create_from("");
    string* str2 = string_create_from("Hello");

    size_t writed = string_write(obj, str2);

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->string);
    ck_assert_str_eq(obj->string, str2->string);
    ck_assert_uint_eq(obj->length, 5);
    ck_assert_uint_eq(obj->size, 6);
    ck_assert_uint_eq(writed, 6);

    string_destroy(obj);
}
END_TEST

START_TEST(string_write_test_to_null) {
    string* obj = 0;
    string* str2 = string_create_from("Hello");

    size_t writed = string_write(obj, str2);

    //ck_assert_ptr_nonnull(obj);
    //ck_assert_ptr_nonnull(obj->string);
    //ck_assert_str_eq(obj->string, str2->string);
    //ck_assert_uint_eq(obj->length, 5);
    //ck_assert_uint_eq(obj->size, 6);
    ck_assert_uint_eq(writed, 0);

    string_destroy(obj);
}
END_TEST

START_TEST(string_write_test_from_null) {
    string* obj = string_create_from("");
    string* str2 = 0;

    size_t writed = string_write(obj, str2);

    //ck_assert_ptr_nonnull(obj);
    //ck_assert_ptr_nonnull(obj->string);
    //ck_assert_str_eq(obj->string, str2->string);
    //ck_assert_uint_eq(obj->length, 5);
    //ck_assert_uint_eq(obj->size, 6);
    ck_assert_uint_eq(writed, 0);

    string_destroy(obj);
}
END_TEST

Suite* test_string_write() {
    Suite* su = suite_create(NAME);
    TCase* test_case = tcase_create(NAME);

    tcase_add_test(test_case, string_write_test_overwrite_empty_1);
    tcase_add_test(test_case, string_write_test_overwrite_str);
    tcase_add_test(test_case, string_write_test_overwrite_with_empty);
    tcase_add_test(test_case, string_write_test_overwrite_empty_2);
    tcase_add_test(test_case, string_write_test_to_null);
    tcase_add_test(test_case, string_write_test_from_null);

    suite_add_tcase(su, test_case);

    return su;
}
