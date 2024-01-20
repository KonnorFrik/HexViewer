#include "string_tests.h"

int run_test(Suite* s) {
  SRunner* runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  int fail = srunner_ntests_failed(runner);
  srunner_free(runner);

  return fail;
}

int main() {
    printf("\n\tSTART TEST \033[38;5;46mSTRING\033[0m MODULE\n");
    int failed = 0;

    failed += run_test(test_string_create());

    printf("\n\tfailed: %d\n", failed);
    printf("\t  END TEST \033[38;5;46mSTRING\033[0m MODULE\n");
    return failed;
}
