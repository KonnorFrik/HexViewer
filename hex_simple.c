#include "views/views.h"
#include "formater/hex_formater.h"
#include "str_wrap/wrap.h"

#include <stdio.h>

int main() {
    string* str = string_create();
    str_write(str, "HELLO\n");
    printf(str->string);
    string_destroy(str);
    return 0;
}
