#include "string_tests.h"
#define NAME "\033[38;5;46m str \033[0m \033[38;5;45m cat \033[0m"

START_TEST(str_cat_test_to_empty_1) {
    char* str = "Hello";
    string* obj = string_create();

    //#if TEST_PRINT == 1
    //printf("\n");
    //printf("\t[TEST_DEBUG]: Before write\n");
    //printf("\t[TEST_DEBUG]: obj.str   : '%s'\n", obj->string);
    //printf("\t[TEST_DEBUG]: obj.lenght: %lu\n", obj->length);
    //printf("\t[TEST_DEBUG]: obj.size  : %lu\n", obj->size);
    //#endif

    size_t writed = str_cat(obj, str);

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->string);
    ck_assert_str_eq(obj->string, str);
    ck_assert_uint_eq(obj->length, 5);
    ck_assert_uint_eq(obj->size, 6);
    ck_assert_uint_eq(writed, 6);

    string_destroy(obj);
}
END_TEST

START_TEST(str_cat_test_norm) {
    char* str1 = "Hello";
    char* str2 = " world";

    string* obj = string_create_from(str1);

    size_t writed = str_cat(obj, str2);

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->string);
    ck_assert_str_eq(obj->string, "Hello world");
    ck_assert_uint_eq(obj->length, 11);
    ck_assert_uint_eq(obj->size, 12);
    ck_assert_uint_eq(writed, 7);

    string_destroy(obj);
}
END_TEST

START_TEST(str_cat_test_from_empty) {
    char* str1 = "Hello";
    char* str2 = "";

    string* obj = string_create_from(str1);

    size_t writed = str_cat(obj, str2);

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->string);
    ck_assert_str_eq(obj->string, str1);
    ck_assert_uint_eq(obj->length, 5);
    ck_assert_uint_eq(obj->size, 6);
    ck_assert_uint_eq(writed, 0);

    string_destroy(obj);
}
END_TEST

START_TEST(str_cat_test_to_empty) {
    char* str1 = "";
    char* str2 = "Hello";

    string* obj = string_create_from(str1);
    size_t writed = str_cat(obj, str2);

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->string);
    ck_assert_str_eq(obj->string, str2);
    ck_assert_uint_eq(obj->length, 5);
    ck_assert_uint_eq(obj->size, 6);
    ck_assert_uint_eq(writed, 6);

    string_destroy(obj);
}
END_TEST

START_TEST(str_cat_test_from_null) {
    char* str1 = "Hello";
    char* str2 = 0;

    string* obj = string_create_from(str1);
    size_t writed = str_cat(obj, str2);

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->string);
    ck_assert_str_eq(obj->string, str1);
    ck_assert_uint_eq(obj->length, 5);
    ck_assert_uint_eq(obj->size, 6);
    ck_assert_uint_eq(writed, 0);

    string_destroy(obj);
}
END_TEST

START_TEST(str_cat_test_to_null) {
    char* str2 = "HELLO";

    string* obj = 0;
    size_t writed = str_cat(obj, str2);

    //ck_assert_ptr_nonnull(obj);
    //ck_assert_ptr_nonnull(obj->string);
    //ck_assert_str_eq(obj->string, str1);
    //ck_assert_uint_eq(obj->length, 5);
    //ck_assert_uint_eq(obj->size, 6);
    ck_assert_uint_eq(writed, 0);

    string_destroy(obj);
}
END_TEST

Suite* test_str_cat() {
    Suite* su = suite_create(NAME);
    TCase* test_case = tcase_create(NAME);

    tcase_add_test(test_case, str_cat_test_to_empty_1);
    tcase_add_test(test_case, str_cat_test_norm);
    tcase_add_test(test_case, str_cat_test_from_empty);
    tcase_add_test(test_case, str_cat_test_to_empty);
    tcase_add_test(test_case, str_cat_test_from_null);
    tcase_add_test(test_case, str_cat_test_to_null);

    suite_add_tcase(su, test_case);

    return su;
}

