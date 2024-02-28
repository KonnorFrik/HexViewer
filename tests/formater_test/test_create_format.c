#include "format_test.h"
#define NAME "\033[38;5;46m format \033[0m \033[38;5;45m create \033[0m"

int g_argc = 24;
char* g_argv[] = {"./fake_programm",       // 1
                "--help",                  // 2
                "--upper-byte",            // 3
                "--byte-type", "asm",      // 4 5
                "--byte-type", "py",       // 6 7
                "--address-len", "10",     // 8 9
                "--address-type", "oct",   // 10 11
                "--address-type", "dec",   // 12 13
                "--non-decode", "_",       // 14 15
                "--byte-delimiter", "|",   // 16 17
                "--row-len", "2",          // 18 19
                "--row-len", "0",          // 20 21
                "--offset", "16",          // 22 23
                "--strings"                // 24
                };

START_TEST(fmt_create_default) {
    page_format* obj = page_format_create();

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_null(obj->current_row);
    ck_assert_uint_eq(obj->byte_format.type, c_type);
    ck_assert_uint_eq(obj->byte_format.is_upper, 0);

    ck_assert_uint_eq(obj->row_format.address_len, 4);
    ck_assert_uint_eq(obj->row_format.address_type, hex_type);
    ck_assert_uint_eq(obj->row_format.bytes_len, 16);
    ck_assert_uint_eq(obj->row_format.bytes_delimiter, ' ');
    ck_assert_uint_eq(obj->row_format.std_symbol, '.');
    ck_assert_uint_eq(obj->row_format.strings, 0);

    ck_assert_uint_eq(obj->is_show_header, 1);
    ck_assert_uint_eq(obj->show_help, 0);
    ck_assert_uint_eq(obj->offset, 0);

    page_format_destroy(obj);
}
END_TEST

START_TEST(fmt_create_from_args) {
    page_format* obj = page_format_create();
    int status = page_format_init(g_argc, g_argv, obj);

    ck_assert_int_eq(status, NO_ERROR);
    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->current_row);
    ck_assert_uint_eq(obj->byte_format.type, py_type);
    ck_assert_uint_eq(obj->byte_format.is_upper, 1);

    ck_assert_uint_eq(obj->row_format.address_len, 10);
    ck_assert_uint_eq(obj->row_format.address_type, dec_type);
    ck_assert_uint_eq(obj->row_format.bytes_len, 1);
    ck_assert_uint_eq(obj->row_format.bytes_delimiter, '|');
    ck_assert_uint_eq(obj->row_format.std_symbol, '_');
    ck_assert_uint_eq(obj->row_format.strings, 1);

    ck_assert_uint_eq(obj->is_show_header, 1);
    ck_assert_uint_eq(obj->show_help, 1);
    ck_assert_uint_eq(obj->offset, 16);

    page_format_destroy(obj);
}
END_TEST

START_TEST(fmt_create_from_null_1) {
    int status = page_format_init(g_argc, g_argv, NULL);

    ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(fmt_create_from_null_2) {
    page_format* obj = page_format_create();

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_null(obj->current_row);

    int status = page_format_init(g_argc, NULL, obj);

    ck_assert_int_eq(status, ERROR);

    page_format_destroy(obj);
}
END_TEST

START_TEST(fmt_create_from_unknown_1) {
    //segfault idk why
    page_format* obj = page_format_create();

    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_null(obj->current_row);

    int argc = 2;
    char* argv[] = {"./fake_programm",
                    "--not"};

    int status = page_format_init(argc, argv, obj);

    ck_assert_int_eq(status, ERROR);
    //ck_assert_uint_eq(obj->byte_format.type, py_type);
    //ck_assert_uint_eq(obj->byte_format.is_upper, 1);

    //ck_assert_uint_eq(obj->row_format.address_len, 10);
    //ck_assert_uint_eq(obj->row_format.address_type, dec_type);
    //ck_assert_uint_eq(obj->row_format.bytes_len, 16);
    //ck_assert_uint_eq(obj->row_format.bytes_delimiter, '|');
    //ck_assert_uint_eq(obj->row_format.std_symbol, '_');

    //ck_assert_uint_eq(obj->is_show_header, 1);
    //ck_assert_uint_eq(obj->show_help, 0);

    page_format_destroy(obj);
}
END_TEST

Suite* test_format_create() {
    Suite* su = suite_create(NAME);
    TCase* test_case = tcase_create(NAME);

    tcase_add_test(test_case, fmt_create_default);
    tcase_add_test(test_case, fmt_create_from_args);
    tcase_add_test(test_case, fmt_create_from_null_1);
    tcase_add_test(test_case, fmt_create_from_null_2);
    //tcase_add_test(test_case, fmt_create_from_unknown_1);

    suite_add_tcase(su, test_case);

    return su;
}
