#include "format_test.h"
#define NAME "\033[38;5;46m format \033[0m \033[38;5;45m create \033[0m"

START_TEST(fmt_create_default) {
    page_format* obj = page_format_create();


    ck_assert_ptr_nonnull(obj);
    ck_assert_ptr_nonnull(obj->current_row);
    ck_assert_uint_eq(obj->byte_format.type, c_type);
    ck_assert_uint_eq(obj->row_format.address_len, 4);
    ck_assert_uint_eq(obj->row_format.address_type, hex_type);
    ck_assert_uint_eq(obj->row_format.bytes_len, 16);
    ck_assert_uint_eq(obj->row_format.bytes_delimiter, ' ');
    ck_assert_uint_eq(obj->row_format.std_symbol, '.');
    ck_assert_uint_eq(obj->is_show_header, 1);

    page_format_destroy(obj);
}
END_TEST

Suite* test_format_create() {
    Suite* su = suite_create(NAME);
    TCase* test_case = tcase_create(NAME);

    tcase_add_test(test_case, fmt_create_default);

    suite_add_tcase(su, test_case);

    return su;
}
