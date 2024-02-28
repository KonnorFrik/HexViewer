#include "string_tests/string_tests.h"
#include "formater_test/format_test.h"
#include <check.h>

int run_test(Suite* s) {
  SRunner* runner = srunner_create(s);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  int fail = srunner_ntests_failed(runner);
  srunner_free(runner);

  return fail;
}

int main() {
    printf("\n\tSTART TEST \033[38;5;46mSTRING\033[0m MODULE\n");
    int failed = 0;

    failed += run_test(test_string_create());

    failed += run_test(test_string_write());
    failed += run_test(test_string_cat());

    failed += run_test(test_str_write());
    failed += run_test(test_str_cat());

    failed += run_test(test_string_destroy());
    failed += run_test(test_string_clear());

    failed += run_test(test_str_to_lower());
    failed += run_test(test_str_to_upper());
    failed += run_test(test_string_to_lower());
    failed += run_test(test_string_to_upper());

    printf("\n\t\033[38;2;250;0;0mfailed\033[0m: %d\n", failed);
    printf("\t  END TEST \033[38;5;46mSTRING\033[0m MODULE\n");


    printf("\n\tSTART TEST \033[38;5;46mFORMAT\033[0m MODULE\n");

    failed += run_test(test_format_create());

    printf("\n\t\033[38;2;250;0;0mfailed\033[0m: %d\n", failed);
    printf("\t  END TEST \033[38;5;46mFORMAT\033[0m MODULE\n");
}

