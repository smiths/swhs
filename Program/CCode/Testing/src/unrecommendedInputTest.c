#include "unity.h"
#include "unity_fixture.h"
#include "verify_params.h"

TEST_GROUP(UnrecommendedInput);

TEST_SETUP(UnrecommendedInput){
}

TEST_TEAR_DOWN(UnrecommendedInput){
}

TEST(UnrecommendedInput, testUI01){
    struct parameters params;
    params = load_params("UnrecommendedInput/UI01.txt");
    const char * msg;
    msg = verify_recommended(params);
    TEST_ASSERT_EQUAL_STRING("Warning: It is recommended that 0.1 <= L <= 50", msg);
}

TEST(UnrecommendedInput, testUI02){
    struct parameters params;
    params = load_params("UnrecommendedInput/UI02.txt");
    const char * msg;
    msg = verify_recommended(params);
    TEST_ASSERT_EQUAL_STRING("Warning: It is recommended that 0.1 <= L <= 50", msg);
}
