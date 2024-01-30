#include "format_test.h"

int main() {
    printf("\n\tSTART TEST \033[38;5;46mFORMAT\033[0m MODULE\n");
    int failed = 0;

    failed += run_test(test_format_create());

    printf("\n\t\033[38;2;250;0;0mfailed\033[0m: %d\n", failed);
    printf("\t  END TEST \033[38;5;46mFORMAT\033[0m MODULE\n");
    return failed;
}
