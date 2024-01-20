#include "string_tests.h"
#define NAME "\033[38;5;46m string \033[0m \033[38;5;45m create \033[0m"

START_TEST(string_create_test_1) {
    string* obj = string_create();
    ck_assert_ptr_nonnull(obj);
}
END_TEST

Suite* test_string_create() {
    Suite* su = suite_create(NAME);
    TCase* test_case = tcase_create(NAME);

    tcase_add_test(test_case, string_create_test_1);

    suite_add_tcase(su, test_case);

    return su;
}
