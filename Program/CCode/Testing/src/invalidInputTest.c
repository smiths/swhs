#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "../verify_params.h"
#include <cmocka.h>

static void testFI01(void){
    struct parameters params;
    params = load_params("FaultyInput/FI01.txt");
    int rc = verify_params(params);
    assert_return_code(rc, 0);
}

/*void testFI02(void){
    struct parameters params;
    params = load_params("FaultyInput/FI02.txt");
    assert_return_code(verify_params(params), 0);
}*/

int main(void){
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(testFI01),
        //cmocka_unit_test(testFI02),
        };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
